// ============================================================================
// ClearanceDDSPublisher.h - CLEARANCE's DDS publisher API.
//
// One FClearancePublisher instance owns:
//   - a DomainParticipant on the caller-supplied domain ID
//   - a Publisher entity
//   - six Topics matching the AirspaceTelemetry.idl schema
//   - one DataWriter per topic (Reliability = BEST_EFFORT, matches DIS
//     semantics: fresh data over guaranteed delivery)
//
// Consumer builds a POD struct (defined in AirspaceTelemetry.hpp from the
// fastddsgen output), hands it to the matching Publish*() method, and moves
// on. Everything downstream - CDR serialisation, RTPS framing, discovery,
// wire transmission - is Fast DDS's job.
//
// Six topics mirror the six DIS PDU types:
//   clearance/aircraft/state       AircraftState        (continuous, ~5 Hz)
//   clearance/weapons/fire         FireEvent            (burst on SCRAMBLE)
//   clearance/weapons/detonation   DetonationEvent      (burst on intercept resolve)
//   clearance/radar/emission       EmissionSnapshot     (continuous, ~5 Hz)
//   clearance/radio/transmitter    TransmitterState     (continuous, ~5 Hz)
//   clearance/radio/signal         SignalEvent          (burst on transcribed line)
//
// Pure C++, no Unreal. Public API surface stays engine-free so the same
// module could drop into a Unity native plugin, a ROS 2 bridge, or a
// headless federate. Fast DDS types are hidden behind FClearancePublisher's
// PImpl. - TripleA
// ============================================================================

#pragma once

#include "ClearanceDDS/ClearanceDDSSanity.h"   // for CLEARANCEDDS_API macro block
#include "AirspaceTelemetry.hpp"               // the POD topic data types

#include <cstdint>
#include <memory>

namespace ClearanceDDS
{
	// Forward declaration of the PImpl so we don't leak <fastdds/...> into the
	// public header. Definition lives in ClearanceDDSPublisher.cpp. - TripleA
	class FClearancePublisherImpl;

	class CLEARANCEDDS_API FClearancePublisher
	{
	public:
		// Create the participant + all six writers on the given DDS domain.
		// Returns nullptr on any RTI failure. Domain 0 is the default and
		// matches Fast DDS's out-of-the-box discovery config. - TripleA
		static std::unique_ptr<FClearancePublisher> Create(std::uint32_t DomainId = 0);
		~FClearancePublisher();

		// Non-copyable / non-movable. If a caller needs multiple publishers
		// (multiple exercises, multiple domains) they create multiple. - TripleA
		FClearancePublisher(const FClearancePublisher&) = delete;
		FClearancePublisher& operator=(const FClearancePublisher&) = delete;

		// Publish one instance of each topic. Returns true if the DataWriter
		// accepted the sample. Non-blocking - if the send buffer is full the
		// sample is silently dropped, matching DIS best-effort semantics. - TripleA
		bool PublishAircraftState   (const AircraftState& S);
		bool PublishFireEvent       (const FireEvent& E);
		bool PublishDetonationEvent (const DetonationEvent& E);
		bool PublishEmissionSnapshot(const EmissionSnapshot& S);
		bool PublishTransmitterState(const TransmitterState& T);
		bool PublishSignalEvent     (const SignalEvent& E);

		// Total samples successfully accepted by any DataWriter since
		// creation. Reported in the instructor panel's DDS FEDERATION UI. - TripleA
		std::uint64_t GetTotalPublishedCount() const;

	private:
		FClearancePublisher();
		std::unique_ptr<FClearancePublisherImpl> Impl;
	};
}
