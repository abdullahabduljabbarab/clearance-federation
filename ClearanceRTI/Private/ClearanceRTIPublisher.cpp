// PImpl-hosted implementation of FClearanceRTIPublisher. Owns the RTI
// Connext entity graph: DomainParticipant -> Publisher -> 6 x (Topic,
// DataWriter). Uses RTI's Modern C++ API (dds/dds.hpp) - value semantics,
// RAII, throw-on-error - not the classic C++ API. Modern C++ is what RTI
// itself recommends for new code and matches the eProsima Fast DDS shape
// so consumers can port between the two by swapping the include.
//
// Best-effort QoS on every writer matches the DIS emitter and the Fast
// DDS emitter - one uniform delivery semantics across all three wires. - TripleA

#define CLEARANCERTI_BUILDING  // export the API surface

#include "CoreMinimal.h"  // for THIRD_PARTY_INCLUDES_START/END

#include "ClearanceRTI/ClearanceRTIPublisher.h"

// RTI Modern C++ (dds::dds.hpp) API surface. Pulls in RTI's platform
// headers which include <windows.h> - has to sit inside UE's third-party
// include block so Windows macros (UpdateResource, MoveMemory, ...)
// don't leak into engine code compiled in the same translation unit. - TripleA
#include "Windows/AllowWindowsPlatformTypes.h"
THIRD_PARTY_INCLUDES_START
#include <dds/domain/DomainParticipant.hpp>
#include <dds/pub/Publisher.hpp>
#include <dds/pub/DataWriter.hpp>
#include <dds/pub/qos/DataWriterQos.hpp>
#include <dds/topic/Topic.hpp>
#include <dds/core/policy/CorePolicy.hpp>
#include <dds/core/Exception.hpp>
THIRD_PARTY_INCLUDES_END
#include "Windows/HideWindowsPlatformTypes.h"

#include <atomic>

namespace ClearanceRTI
{
	// Canonical topic names - shared with the ClearanceDDS runtime so a
	// Fast DDS subscriber on the same domain would match an RTI publisher
	// on the same topic name. In practice we keep the two on different
	// domain IDs to isolate discovery traffic, but the naming stays
	// consistent so the two runtimes are drop-in replaceable at the wire
	// level for tooling that treats them as equivalent DDS speakers. - TripleA
	namespace Topics
	{
		constexpr const char* kAircraftState    = "clearance/aircraft/state";
		constexpr const char* kFireEvent        = "clearance/weapons/fire";
		constexpr const char* kDetonationEvent  = "clearance/weapons/detonation";
		constexpr const char* kEmissionSnapshot = "clearance/radar/emission";
		constexpr const char* kTransmitterState = "clearance/radio/transmitter";
		constexpr const char* kSignalEvent      = "clearance/radio/signal";
	}

	class FClearanceRTIPublisherImpl
	{
	public:
		// Modern C++ RTI entities are value types with a `dds::core::null`
		// sentinel for the uninitialised state. Default-construct as null
		// so a failed Init() leaves the impl in a safe teardown state. - TripleA
		dds::domain::DomainParticipant Participant = dds::core::null;
		dds::pub::Publisher            Pub         = dds::core::null;

		dds::topic::Topic<AircraftState>    AircraftTopic    = dds::core::null;
		dds::topic::Topic<FireEvent>        FireTopic        = dds::core::null;
		dds::topic::Topic<DetonationEvent>  DetonationTopic  = dds::core::null;
		dds::topic::Topic<EmissionSnapshot> EmissionTopic    = dds::core::null;
		dds::topic::Topic<TransmitterState> TransmitterTopic = dds::core::null;
		dds::topic::Topic<SignalEvent>      SignalTopic      = dds::core::null;

		dds::pub::DataWriter<AircraftState>    AircraftWriter    = dds::core::null;
		dds::pub::DataWriter<FireEvent>        FireWriter        = dds::core::null;
		dds::pub::DataWriter<DetonationEvent>  DetonationWriter  = dds::core::null;
		dds::pub::DataWriter<EmissionSnapshot> EmissionWriter    = dds::core::null;
		dds::pub::DataWriter<TransmitterState> TransmitterWriter = dds::core::null;
		dds::pub::DataWriter<SignalEvent>      SignalWriter      = dds::core::null;

		std::atomic<std::uint64_t> Published{ 0 };

		// Last error string from Init - Init swallows the RTI exception to
		// keep the runtime clean, but a diagnostic caller can pull the
		// message out of the impl for logging. - TripleA
		std::string LastInitError;

		bool Init(std::uint32_t DomainId)
		{
			try
			{
				Participant = dds::domain::DomainParticipant(DomainId);
				Pub         = dds::pub::Publisher(Participant);

				dds::pub::qos::DataWriterQos WriterQos = Pub.default_datawriter_qos();
				WriterQos << dds::core::policy::Reliability::BestEffort();

				AircraftTopic    = dds::topic::Topic<AircraftState>   (Participant, Topics::kAircraftState);
				FireTopic        = dds::topic::Topic<FireEvent>       (Participant, Topics::kFireEvent);
				DetonationTopic  = dds::topic::Topic<DetonationEvent> (Participant, Topics::kDetonationEvent);
				EmissionTopic    = dds::topic::Topic<EmissionSnapshot>(Participant, Topics::kEmissionSnapshot);
				TransmitterTopic = dds::topic::Topic<TransmitterState>(Participant, Topics::kTransmitterState);
				SignalTopic      = dds::topic::Topic<SignalEvent>     (Participant, Topics::kSignalEvent);

				AircraftWriter    = dds::pub::DataWriter<AircraftState>   (Pub, AircraftTopic,    WriterQos);
				FireWriter        = dds::pub::DataWriter<FireEvent>       (Pub, FireTopic,        WriterQos);
				DetonationWriter  = dds::pub::DataWriter<DetonationEvent> (Pub, DetonationTopic,  WriterQos);
				EmissionWriter    = dds::pub::DataWriter<EmissionSnapshot>(Pub, EmissionTopic,    WriterQos);
				TransmitterWriter = dds::pub::DataWriter<TransmitterState>(Pub, TransmitterTopic, WriterQos);
				SignalWriter      = dds::pub::DataWriter<SignalEvent>     (Pub, SignalTopic,      WriterQos);

				return true;
			}
			catch (const dds::core::Exception& Ex)
			{
				LastInitError = Ex.what();
				return false;
			}
			catch (const std::exception& Ex)
			{
				LastInitError = Ex.what();
				return false;
			}
		}

		// One templated write path used by every Publish* method. Catches
		// the RTI exception types (dds::core::Error hierarchy) so a
		// transient publish failure never propagates back into the game
		// thread - matches the DIS emitter's swallow-and-count-drops
		// semantics. - TripleA
		template <typename W, typename T>
		bool Write(W& Writer, const T& Sample)
		{
			if (Writer == dds::core::null) { return false; }
			try
			{
				Writer.write(Sample);
				Published.fetch_add(1, std::memory_order_relaxed);
				return true;
			}
			catch (const dds::core::Exception&)
			{
				return false;
			}
		}
	};

	// ------------------------------------------------------------------
	//  Public API delegation
	// ------------------------------------------------------------------

	namespace
	{
		// File-scope holder for the most recent Create() failure message,
		// populated when Init throws. Read via GetLastCreateError(). - TripleA
		std::string GLastCreateError;
	}

	std::unique_ptr<FClearanceRTIPublisher> FClearanceRTIPublisher::Create(std::uint32_t DomainId)
	{
		std::unique_ptr<FClearanceRTIPublisher> Instance(new FClearanceRTIPublisher());
		if (!Instance->Impl->Init(DomainId))
		{
			GLastCreateError = Instance->Impl->LastInitError;
			return nullptr;
		}
		GLastCreateError.clear();
		return Instance;
	}

	std::string FClearanceRTIPublisher::GetLastCreateError()
	{
		return GLastCreateError;
	}

	FClearanceRTIPublisher::FClearanceRTIPublisher()
		: Impl(std::make_unique<FClearanceRTIPublisherImpl>())
	{}

	FClearanceRTIPublisher::~FClearanceRTIPublisher() = default;

	bool FClearanceRTIPublisher::PublishAircraftState(const AircraftState& S)
	{ return Impl->Write(Impl->AircraftWriter, S); }

	bool FClearanceRTIPublisher::PublishFireEvent(const FireEvent& E)
	{ return Impl->Write(Impl->FireWriter, E); }

	bool FClearanceRTIPublisher::PublishDetonationEvent(const DetonationEvent& E)
	{ return Impl->Write(Impl->DetonationWriter, E); }

	bool FClearanceRTIPublisher::PublishEmissionSnapshot(const EmissionSnapshot& S)
	{ return Impl->Write(Impl->EmissionWriter, S); }

	bool FClearanceRTIPublisher::PublishTransmitterState(const TransmitterState& T)
	{ return Impl->Write(Impl->TransmitterWriter, T); }

	bool FClearanceRTIPublisher::PublishSignalEvent(const SignalEvent& E)
	{ return Impl->Write(Impl->SignalWriter, E); }

	std::uint64_t FClearanceRTIPublisher::GetTotalPublishedCount() const
	{ return Impl->Published.load(std::memory_order_relaxed); }
}
