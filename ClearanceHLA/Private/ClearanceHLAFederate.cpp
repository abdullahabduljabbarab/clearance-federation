// PImpl-hosted implementation of FClearanceHLAFederate. Owns the OpenRTI
// entity graph: RTIambassador -> FederateAmbassador (null-callback) -> the
// declared object class handle -> per-callsign object instance handles.
//
// IEEE 1516-2010 (HLA-Evolved) semantics throughout - HLAinteger* / HLAfloat*
// encoding helpers from the rti1516e::encoding namespace for attribute
// values, NullFederateAmbassador as a base for the callback interface so
// we only override the callbacks we actually need. - TripleA

#define CLEARANCEHLA_BUILDING

#include "CoreMinimal.h"  // for THIRD_PARTY_INCLUDES_START/END

#include "ClearanceHLA/ClearanceHLAFederate.h"

// OpenRTI's rti1516e headers pull in <windows.h> transitively, plus some
// legacy C-style casts UE flags as warnings-as-errors. Wrap with UE's
// third-party include guard + Windows push/pop so the pollution stays
// contained. Same shape used for RTI Connext + Fast DDS. - TripleA
#include "Windows/AllowWindowsPlatformTypes.h"
THIRD_PARTY_INCLUDES_START
#include <RTI/RTI1516.h>
#include <RTI/RTIambassador.h>
#include <RTI/RTIambassadorFactory.h>
#include <RTI/NullFederateAmbassador.h>
#include <RTI/encoding/BasicDataElements.h>
THIRD_PARTY_INCLUDES_END
#include "Windows/HideWindowsPlatformTypes.h"

#include <atomic>
#include <chrono>
#include <cstdio>
#include <map>
#include <sstream>

namespace ClearanceHLA
{
	using namespace rti1516e;

	namespace
	{
		// Widen std::string -> std::wstring for the RTI's wide-char API.
		// IEEE 1516-2010 defines every string as UTF-16 (wchar_t on Windows).
		// Simple ASCII-only widen suffices for our callsigns + federation
		// names. - TripleA
		inline std::wstring Widen(const std::string& S)
		{
			return std::wstring(S.begin(), S.end());
		}

		// Encode a plain double into a HLA VariableLengthData wrapper - the
		// standard IEEE 1516-2010 marshalling for a scalar attribute value.
		// HLAfloat64BE = big-endian IEEE 754 double, which is what RPR-FOM
		// attributes like WorldLocation.X expect. - TripleA
		inline VariableLengthData EncodeDouble(double V)
		{
			HLAfloat64BE E(V);
			return E.encode();
		}

		inline VariableLengthData EncodeFloat(float V)
		{
			HLAfloat32BE E(V);
			return E.encode();
		}

		inline VariableLengthData EncodeUInt16(std::uint16_t V)
		{
			HLAinteger16BE E(static_cast<Integer16>(V));
			return E.encode();
		}

		// One-time diagnostic buffer for the most recent join error. - TripleA
		std::string GLastJoinError;

		// Once-per-second-rate-limited stderr line so we can see what
		// updateAttributeValues is throwing without flooding logs. - TripleA
		void LogUpdateFailure(const std::string& Msg)
		{
			static std::chrono::steady_clock::time_point LastLog;
			const auto Now = std::chrono::steady_clock::now();
			if (std::chrono::duration_cast<std::chrono::seconds>(Now - LastLog).count() < 1) { return; }
			LastLog = Now;
			// Route through UE_LOG so the message shows up in the Output
			// Log next to the [HLA] EmitStates lines. Earlier stderr path
			// went nowhere visible in the editor. - TripleA
			UE_LOG(LogTemp, Warning, TEXT("[HLA] %s"), *FString(Msg.c_str()));
		}
	}

	// Callback receiver. NullFederateAmbassador implements every pure
	// virtual with a no-op, so we only override the ones we actually
	// care about. For publish-only MVP we don't need any callbacks -
	// but the class instance is still required for Join. - TripleA
	class FClearanceFederateAmbassador : public NullFederateAmbassador
	{
	public:
		// Empty - MVP is publish-only. Attribute subscription + interaction
		// callbacks come later when the sim needs to ingest federate
		// updates from peers. - TripleA
	};

	class FClearanceHLAFederateImpl
	{
	public:
		std::unique_ptr<RTIambassador> Amb;
		std::unique_ptr<FClearanceFederateAmbassador> Fed;

		// Handles resolved at Join time. The object class handle points
		// at ATCManagedAircraft; attribute handles cover the four fields
		// our FOM extension declares. Base RPR-FOM 2.0 attributes (Marking,
		// EntityIdentifier, WorldLocation*) would require also loading the
		// SISO RPR-FOM base module - not shipped, so publish is limited to
		// what our own extension defines. - TripleA
		ObjectClassHandle AircraftClass;
		AttributeHandle   AttrSquawkCode;
		AttributeHandle   AttrFlightPhase;
		AttributeHandle   AttrActiveClearance;
		AttributeHandle   AttrATCFacility;

		// One object instance per callsign. Registered lazily on first
		// UpdateAircraftAttributes call. - TripleA
		std::map<std::string, ObjectInstanceHandle> InstanceByCallsign;

		std::atomic<std::uint64_t> UpdatesSent{ 0 };
		bool bJoined = false;

		bool Join(const std::string& FederationName,
		          const std::string& FederateName,
		          const std::string& FomModulePath)
		{
			try
			{
				RTIambassadorFactory Factory;
				Amb = Factory.createRTIambassador();
				Fed = std::make_unique<FClearanceFederateAmbassador>();

				// Modern-connect-style API: connect + join in one call
				// against the ambassador factory. rtinode listener has to
				// be reachable via the default OpenRTI protocol - if
				// there's no rtinode running the connect throws
				// ConnectionFailed which we catch below. - TripleA
				Amb->connect(*Fed, HLA_EVOKED);

				// Try create - it's idempotent-with-exception in IEEE 1516,
				// so catch FederationExecutionAlreadyExists and continue. - TripleA
				try
				{
					std::vector<std::wstring> FomModules;
					FomModules.push_back(Widen(FomModulePath));
					Amb->createFederationExecution(Widen(FederationName), FomModules);
				}
				catch (const FederationExecutionAlreadyExists&)
				{
					// Fine - another federate got there first. - TripleA
				}

				Amb->joinFederationExecution(Widen(FederateName), Widen(FederationName));
				bJoined = true;

				// Resolve object class + attribute handles from the FOM.
				// If the FOM doesn't declare ATCManagedAircraft this
				// throws NameNotFound and we bail. - TripleA
				AircraftClass       = Amb->getObjectClassHandle(L"HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.Aircraft.ATCManagedAircraft");
				AttrSquawkCode      = Amb->getAttributeHandle(AircraftClass, L"SquawkCode");
				AttrFlightPhase     = Amb->getAttributeHandle(AircraftClass, L"FlightPhase");
				AttrActiveClearance = Amb->getAttributeHandle(AircraftClass, L"ActiveClearance");
				AttrATCFacility     = Amb->getAttributeHandle(AircraftClass, L"ATCFacility");

				// Declare publication of the attribute set. Subscription
				// would come next if we were reading peer traffic, but MVP
				// is publish-only. - TripleA
				AttributeHandleSet PubAttrs;
				PubAttrs.insert(AttrSquawkCode);
				PubAttrs.insert(AttrFlightPhase);
				PubAttrs.insert(AttrActiveClearance);
				PubAttrs.insert(AttrATCFacility);
				Amb->publishObjectClassAttributes(AircraftClass, PubAttrs);

				return true;
			}
			catch (const Exception&)
			{
				// Avoid Ex.what() - see Register() for the cross-DLL heap
				// reason. Any RTI-side detail comes back via rtinode's log
				// or Wireshark; here we just flag which stage failed. - TripleA
				GLastJoinError = "RTI Exception during Join (federation / handles / publish)";
				return false;
			}
			catch (const std::exception&)
			{
				GLastJoinError = "std::exception during Join";
				return false;
			}
		}

		bool Register(const std::string& Callsign)
		{
			if (!bJoined) { return false; }
			if (InstanceByCallsign.count(Callsign)) { return true; }
			try
			{
				// Use the auto-name overload of registerObjectInstance -
				// the named overload requires reserveObjectInstanceName
				// (with a callback pump waiting for
				// objectInstanceNameReservationSucceeded) before the name
				// can be used. RTI assigns names like "HLA1234"; we still
				// key our own map by callsign so the sim tick lookup is
				// O(log N). Peer federates will see the RTI-generated name
				// in discoverObjectInstance but that's cosmetic - the
				// class + attribute values are what matter. - TripleA
				ObjectInstanceHandle H = Amb->registerObjectInstance(AircraftClass);
				InstanceByCallsign[Callsign] = H;
				return true;
			}
			catch (const Exception&)
			{
				LogUpdateFailure("registerObjectInstance('" + Callsign + "') threw RTI Exception");
				return false;
			}
		}

		bool Update(const AircraftStateWire& S)
		{
			if (!bJoined) { return false; }
			auto It = InstanceByCallsign.find(S.Callsign);
			if (It == InstanceByCallsign.end())
			{
				if (!Register(S.Callsign)) { return false; }
				It = InstanceByCallsign.find(S.Callsign);
			}
			try
			{
				AttributeHandleValueMap Values;
				Values[AttrSquawkCode]  = EncodeUInt16(S.SquawkCode);

				// FlightPhase is an HLA enumeration - underlying representation
				// is HLAinteger16BE per our FOM's FlightPhaseEnum datatype
				// declaration. Encode the raw enum ordinal. - TripleA
				Values[AttrFlightPhase] = EncodeUInt16(static_cast<std::uint16_t>(S.FlightPhase));

				// ActiveClearance + ATCFacility are HLAunicodeString - null-
				// terminated UTF-16 wire representation. Encoded via
				// HLAunicodeString which handles the length prefix. Populated
				// with placeholder strings for MVP; wire will carry per-
				// aircraft clearance text once the ClearanceLog integration
				// lands on the sim side. - TripleA
				const std::wstring WCallsign(S.Callsign.begin(), S.Callsign.end());
				HLAunicodeString CallsignStr(WCallsign);
				Values[AttrActiveClearance] = CallsignStr.encode();

				HLAunicodeString FacilityStr(L"CLR_APP");
				Values[AttrATCFacility] = FacilityStr.encode();

				VariableLengthData UserTag;  // empty user tag
				Amb->updateAttributeValues(It->second, Values, UserTag);
				UpdatesSent.fetch_add(1, std::memory_order_relaxed);
				return true;
			}
			catch (const Exception&)
			{
				// See Register() for the cross-DLL heap reason we avoid
				// touching Ex.what(). - TripleA
				LogUpdateFailure("updateAttributeValues threw RTI Exception");
				return false;
			}
			catch (const std::exception&)
			{
				LogUpdateFailure("updateAttributeValues threw std::exception");
				return false;
			}
		}

		void Resign()
		{
			if (!Amb || !bJoined) { return; }
			try
			{
				Amb->resignFederationExecution(NO_ACTION);
			}
			catch (const Exception&) {}
			try
			{
				Amb->disconnect();
			}
			catch (const Exception&) {}
			bJoined = false;
			InstanceByCallsign.clear();
		}

		~FClearanceHLAFederateImpl()
		{
			Resign();
		}
	};

	// ------------------------------------------------------------------
	//  Public API delegation
	// ------------------------------------------------------------------

	bool FClearanceHLAFederate::CreateFederation(const std::string& FederationName,
	                                             const std::string& FomModulePath)
	{
		try
		{
			RTIambassadorFactory Factory;
			auto Amb = Factory.createRTIambassador();
			FClearanceFederateAmbassador NullFed;
			Amb->connect(NullFed, HLA_EVOKED);
			try
			{
				std::vector<std::wstring> FomModules;
				FomModules.push_back(Widen(FomModulePath));
				Amb->createFederationExecution(Widen(FederationName), FomModules);
			}
			catch (const FederationExecutionAlreadyExists&) {}
			Amb->disconnect();
			return true;
		}
		catch (const Exception&)
		{
			return false;
		}
	}

	std::unique_ptr<FClearanceHLAFederate> FClearanceHLAFederate::Join(
		const std::string& FederationName,
		const std::string& FederateName,
		const std::string& FomModulePath)
	{
		std::unique_ptr<FClearanceHLAFederate> Instance(new FClearanceHLAFederate());
		if (!Instance->Impl->Join(FederationName, FederateName, FomModulePath))
		{
			return nullptr;
		}
		return Instance;
	}

	FClearanceHLAFederate::FClearanceHLAFederate()
		: Impl(std::make_unique<FClearanceHLAFederateImpl>())
	{}

	FClearanceHLAFederate::~FClearanceHLAFederate() = default;

	bool FClearanceHLAFederate::RegisterAircraftInstance(const std::string& Callsign)
	{
		return Impl->Register(Callsign);
	}

	bool FClearanceHLAFederate::UpdateAircraftAttributes(const AircraftStateWire& S)
	{
		return Impl->Update(S);
	}

	bool FClearanceHLAFederate::PublishAircraftState(const AircraftStateWire& S)
	{
		return Impl->Update(S);
	}

	void FClearanceHLAFederate::Resign()
	{
		Impl->Resign();
	}

	std::uint64_t FClearanceHLAFederate::GetTotalUpdatesCount() const
	{
		return Impl->UpdatesSent.load(std::memory_order_relaxed);
	}

	bool FClearanceHLAFederate::IsJoined() const
	{
		return Impl->bJoined;
	}

	std::string FClearanceHLAFederate::GetLastJoinError()
	{
		return GLastJoinError;
	}
}
