// ============================================================================
// ClearanceHLAFederate.h - CLEARANCE's IEEE 1516-2010 (HLA Evolved) federate
//                          facade.
//
// Sibling to FClearancePublisher (ClearanceDDS) and FClearanceRTIPublisher
// (ClearanceRTI). Same isolation discipline: pure C++ public API, RTI
// ambassador types hidden behind a PImpl, engine-free surface so the
// module could drop into a Unity project, a headless federate CLI, or a
// ROS 2 bridge with no source changes.
//
// One FClearanceHLAFederate instance owns:
//   - an rti1516e::RTIambassador (client connection to the RTI)
//   - a companion FederateAmbassador subclass to receive callbacks
//   - the six object class + interaction handles from the RPR-FOM 2.0
//     base module + CLEARANCE's extension FOM
//     (Plugins/ClearanceSim/FOM/ClearanceRPR-FOM.xml)
//   - the local object instances CLEARANCE publishes on (one per
//     tracked aircraft)
//
// Simplified single-topic API for MVP - only AircraftState publication
// wired in. Fire / Detonation / Emission / Transmitter / Signal follow
// the same pattern and can be added in a follow-up without touching
// the public surface (same POD types the RTI + DDS facades accept). - TripleA
// ============================================================================

#pragma once

#include "ClearanceHLA/ClearanceHLAExport.h"

#include <cstdint>
#include <memory>
#include <string>

namespace ClearanceHLA
{
	// Forward declaration - impl body lives in ClearanceHLAFederate.cpp
	// so no rti1516e headers leak through the public API. - TripleA
	class FClearanceHLAFederateImpl;

	// Plain-old-data view of an aircraft attribute update. Deliberately
	// engine-free (no FName, no FVector) - the ClearanceSim-side adapter
	// converts FAircraftState to this at the boundary, same pattern the
	// DDS + RTI adapters use for their generated IDL types. - TripleA
	struct AircraftStateWire
	{
		std::string Callsign;
		std::uint16_t EntityNumber = 0;
		std::uint16_t SiteId = 1;
		std::uint16_t ApplicationId = 1;
		std::uint8_t  ForceId = 0;              // 0=Other, 1=Friendly, 2=Hostile, 3=Neutral
		std::uint8_t  TrueAffiliation = 0;      // God-view truth for instructor scope
		std::uint16_t SquawkCode = 0;
		std::uint8_t  ActiveEmergency = 0;
		std::uint8_t  FlightPhase = 0;

		// ECEF metres + m/s + radians (same units the DIS + DDS wires
		// use - no unit conversion needed at the HLA boundary). - TripleA
		double XMeters = 0.0;
		double YMeters = 0.0;
		double ZMeters = 0.0;
		float  VxMps = 0.f;
		float  VyMps = 0.f;
		float  VzMps = 0.f;
		float  PsiRad = 0.f;
		float  ThetaRad = 0.f;
		float  PhiRad = 0.f;
	};

	class CLEARANCEHLA_API FClearanceHLAFederate
	{
	public:
		// Join a federation execution. FederationName + FederateName +
		// FomModulePath tuple is the standard IEEE 1516-2010 join
		// parameter set. If the federation doesn't exist yet the RTI
		// will refuse the join - creation is a separate concern
		// (Create() static below). Returns nullptr on any RTI error;
		// caller can pull the exception message via GetLastJoinError(). - TripleA
		static std::unique_ptr<FClearanceHLAFederate> Join(
			const std::string& FederationName,
			const std::string& FederateName,
			const std::string& FomModulePath);

		// Create the federation execution (idempotent - returns true if it
		// already exists). Requires a valid RTI to talk to; if there's no
		// running rtinode this returns false. - TripleA
		static bool CreateFederation(
			const std::string& FederationName,
			const std::string& FomModulePath);

		~FClearanceHLAFederate();

		FClearanceHLAFederate(const FClearanceHLAFederate&) = delete;
		FClearanceHLAFederate& operator=(const FClearanceHLAFederate&) = delete;

		// Register an object instance for the local ATCManagedAircraft
		// class (from the CLEARANCE FOM extension). Called once per new
		// callsign that appears in the sim. Returns false if the object
		// class isn't published or the callsign already has an instance. - TripleA
		bool RegisterAircraftInstance(const std::string& Callsign);

		// Send an attribute update for an already-registered aircraft.
		// Non-blocking - if the RTI queue is full the update is dropped
		// (matches DIS best-effort semantics). Returns true if the
		// attribute-map was accepted by the RTIambassador. - TripleA
		bool UpdateAircraftAttributes(const AircraftStateWire& S);

		// Convenience path - registers the instance if it doesn't exist,
		// then updates. Matches the tick-loop shape the DIS/DDS/RTI
		// emitters already use (one call per aircraft per tick). - TripleA
		bool PublishAircraftState(const AircraftStateWire& S);

		// Resign from the federation and destroy the RTIambassador.
		// Called from the destructor as well but exposed for explicit
		// tear-down from console/panel STOP paths. - TripleA
		void Resign();

		// Total attribute updates successfully sent since Join.
		// Drives the panel activity indicators. - TripleA
		std::uint64_t GetTotalUpdatesCount() const;

		// True while the underlying RTIambassador is connected + joined.
		// Flips to false on Resign or on RTI-side lost-connection. - TripleA
		bool IsJoined() const;

		// Diagnostic hook for FAILED joins - Join() returns nullptr and
		// stashes the RTI exception text here. - TripleA
		static std::string GetLastJoinError();

	private:
		FClearanceHLAFederate();
		std::unique_ptr<FClearanceHLAFederateImpl> Impl;
	};
}
