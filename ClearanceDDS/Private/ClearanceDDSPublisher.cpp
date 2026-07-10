// PImpl-hosted implementation of FClearancePublisher. Owns the Fast DDS
// entity graph: DomainParticipant -> Publisher -> 6 x (Topic, DataWriter).
// Best-effort QoS matches the DIS delivery semantics we already publish,
// so a federation observer gets consistent freshness guarantees whichever
// wire it's reading.
//
// TypeSupport objects are registered on the participant once at construction
// so all six writers can reference their generated PubSubType by name. - TripleA

#include "ClearanceDDS/ClearanceDDSPublisher.h"

#include "AirspaceTelemetryPubSubTypes.hpp"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/qos/DomainParticipantQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/topic/qos/TopicQos.hpp>

#include <atomic>

namespace ClearanceDDS
{
	using namespace eprosima::fastdds::dds;

	// Topic name constants - one canonical string per topic so publisher +
	// subscriber agree on the DDS partition without stringly-typed drift. - TripleA
	namespace Topics
	{
		constexpr const char* kAircraftState    = "clearance/aircraft/state";
		constexpr const char* kFireEvent        = "clearance/weapons/fire";
		constexpr const char* kDetonationEvent  = "clearance/weapons/detonation";
		constexpr const char* kEmissionSnapshot = "clearance/radar/emission";
		constexpr const char* kTransmitterState = "clearance/radio/transmitter";
		constexpr const char* kSignalEvent      = "clearance/radio/signal";
	}

	class FClearancePublisherImpl
	{
	public:
		DomainParticipant* Participant  = nullptr;
		Publisher*         Publisher_   = nullptr;

		TypeSupport AircraftStateType   { new AircraftStatePubSubType() };
		TypeSupport FireEventType       { new FireEventPubSubType() };
		TypeSupport DetonationEventType { new DetonationEventPubSubType() };
		TypeSupport EmissionType        { new EmissionSnapshotPubSubType() };
		TypeSupport TransmitterType     { new TransmitterStatePubSubType() };
		TypeSupport SignalType          { new SignalEventPubSubType() };

		Topic* AircraftTopic    = nullptr;
		Topic* FireTopic        = nullptr;
		Topic* DetonationTopic  = nullptr;
		Topic* EmissionTopic    = nullptr;
		Topic* TransmitterTopic = nullptr;
		Topic* SignalTopic      = nullptr;

		DataWriter* AircraftWriter    = nullptr;
		DataWriter* FireWriter        = nullptr;
		DataWriter* DetonationWriter  = nullptr;
		DataWriter* EmissionWriter    = nullptr;
		DataWriter* TransmitterWriter = nullptr;
		DataWriter* SignalWriter      = nullptr;

		std::atomic<std::uint64_t> Published{ 0 };

		bool Init(std::uint32_t DomainId)
		{
			DomainParticipantFactory* Factory = DomainParticipantFactory::get_instance();
			if (!Factory) { return false; }

			Participant = Factory->create_participant(DomainId, PARTICIPANT_QOS_DEFAULT);
			if (!Participant) { return false; }

			// Register all six generated types on the participant so every
			// downstream Topic can be created by type name. - TripleA
			AircraftStateType.register_type(Participant);
			FireEventType.register_type(Participant);
			DetonationEventType.register_type(Participant);
			EmissionType.register_type(Participant);
			TransmitterType.register_type(Participant);
			SignalType.register_type(Participant);

			Publisher_ = Participant->create_publisher(PUBLISHER_QOS_DEFAULT);
			if (!Publisher_) { return false; }

			// Best-effort QoS = drop-old-if-newer. Matches our DIS emitter
			// (UDP fire-and-forget). Reliable would be more robust but adds
			// latency and back-pressure - wrong shape for realtime telemetry. - TripleA
			DataWriterQos WriterQos = DATAWRITER_QOS_DEFAULT;
			WriterQos.reliability().kind = BEST_EFFORT_RELIABILITY_QOS;

			auto MakeTopic = [&](const char* Name, TypeSupport& Type) -> Topic*
			{
				return Participant->create_topic(Name, Type.get_type_name(), TOPIC_QOS_DEFAULT);
			};

			AircraftTopic    = MakeTopic(Topics::kAircraftState,    AircraftStateType);
			FireTopic        = MakeTopic(Topics::kFireEvent,        FireEventType);
			DetonationTopic  = MakeTopic(Topics::kDetonationEvent,  DetonationEventType);
			EmissionTopic    = MakeTopic(Topics::kEmissionSnapshot, EmissionType);
			TransmitterTopic = MakeTopic(Topics::kTransmitterState, TransmitterType);
			SignalTopic      = MakeTopic(Topics::kSignalEvent,      SignalType);

			if (!AircraftTopic || !FireTopic || !DetonationTopic ||
			    !EmissionTopic || !TransmitterTopic || !SignalTopic) { return false; }

			AircraftWriter    = Publisher_->create_datawriter(AircraftTopic,    WriterQos);
			FireWriter        = Publisher_->create_datawriter(FireTopic,        WriterQos);
			DetonationWriter  = Publisher_->create_datawriter(DetonationTopic,  WriterQos);
			EmissionWriter    = Publisher_->create_datawriter(EmissionTopic,    WriterQos);
			TransmitterWriter = Publisher_->create_datawriter(TransmitterTopic, WriterQos);
			SignalWriter      = Publisher_->create_datawriter(SignalTopic,      WriterQos);

			return AircraftWriter && FireWriter && DetonationWriter
			    && EmissionWriter && TransmitterWriter && SignalWriter;
		}

		~FClearancePublisherImpl()
		{
			if (!Participant) { return; }
			// Order matters: writers -> topics -> publisher -> participant.
			// Fast DDS's delete_contained_entities cleans the whole graph in
			// one shot - much simpler than tearing down each entity. - TripleA
			Participant->delete_contained_entities();
			DomainParticipantFactory::get_instance()->delete_participant(Participant);
			Participant = nullptr;
		}

		// SFINAE-free templated write helper - one line per PublishX. - TripleA
		template <typename T>
		bool Write(DataWriter* Writer, const T& Sample)
		{
			if (!Writer) { return false; }
			// DataWriter::write takes a non-const void* - safe because Fast
			// DDS serialises to CDR without mutating the source. Cast const
			// away here rather than at every call site. Returns a
			// ReturnCode_t (int32_t) that we compare to RETCODE_OK. - TripleA
			const ReturnCode_t Rc = Writer->write(const_cast<T*>(&Sample));
			const bool bOk = (Rc == RETCODE_OK);
			if (bOk) { Published.fetch_add(1, std::memory_order_relaxed); }
			return bOk;
		}
	};

	// ------------------------------------------------------------------
	//  Public API delegation
	// ------------------------------------------------------------------

	std::unique_ptr<FClearancePublisher> FClearancePublisher::Create(std::uint32_t DomainId)
	{
		std::unique_ptr<FClearancePublisher> Instance(new FClearancePublisher());
		if (!Instance->Impl->Init(DomainId)) { return nullptr; }
		return Instance;
	}

	FClearancePublisher::FClearancePublisher()
		: Impl(std::make_unique<FClearancePublisherImpl>())
	{}

	FClearancePublisher::~FClearancePublisher() = default;

	bool FClearancePublisher::PublishAircraftState(const AircraftState& S)
	{ return Impl->Write(Impl->AircraftWriter, S); }

	bool FClearancePublisher::PublishFireEvent(const FireEvent& E)
	{ return Impl->Write(Impl->FireWriter, E); }

	bool FClearancePublisher::PublishDetonationEvent(const DetonationEvent& E)
	{ return Impl->Write(Impl->DetonationWriter, E); }

	bool FClearancePublisher::PublishEmissionSnapshot(const EmissionSnapshot& S)
	{ return Impl->Write(Impl->EmissionWriter, S); }

	bool FClearancePublisher::PublishTransmitterState(const TransmitterState& T)
	{ return Impl->Write(Impl->TransmitterWriter, T); }

	bool FClearancePublisher::PublishSignalEvent(const SignalEvent& E)
	{ return Impl->Write(Impl->SignalWriter, E); }

	std::uint64_t FClearancePublisher::GetTotalPublishedCount() const
	{ return Impl->Published.load(std::memory_order_relaxed); }
}
