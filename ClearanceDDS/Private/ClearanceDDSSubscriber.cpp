// PImpl for FClearanceSubscriber. Owns the participant + one reader per
// topic. Each reader has its own listener; the listener's on_data_available
// callback dispatches to the user's OnX handler through the FSubscriberHandlers
// struct. Handlers run on the FastDDS transport thread - keep them cheap. - TripleA

#include "ClearanceDDS/ClearanceDDSSubscriber.h"

#include "AirspaceTelemetryPubSubTypes.hpp"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/qos/DomainParticipantQos.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include <atomic>

namespace ClearanceDDS
{
	using namespace eprosima::fastdds::dds;

	// ------------------------------------------------------------------
	//  Per-topic listener. Templated so we get one class per POD sample
	//  type without hand-rolling six copies. The listener holds a pointer
	//  to the user-supplied std::function and calls it on each sample. - TripleA
	// ------------------------------------------------------------------
	template <typename SampleT>
	class TTopicListener : public DataReaderListener
	{
	public:
		std::function<void(const SampleT&)>* Handler = nullptr;
		std::atomic<std::uint64_t>*          Counter = nullptr;

		void on_data_available(DataReader* Reader) override
		{
			SampleT Sample;
			SampleInfo Info;
			while (Reader->take_next_sample(&Sample, &Info) == RETCODE_OK)
			{
				if (Info.valid_data)
				{
					if (Counter) { Counter->fetch_add(1, std::memory_order_relaxed); }
					if (Handler && *Handler) { (*Handler)(Sample); }
				}
			}
		}
	};

	class FClearanceSubscriberImpl
	{
	public:
		DomainParticipant* Participant  = nullptr;
		Subscriber*        Subscriber_  = nullptr;

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

		DataReader* AircraftReader    = nullptr;
		DataReader* FireReader        = nullptr;
		DataReader* DetonationReader  = nullptr;
		DataReader* EmissionReader    = nullptr;
		DataReader* TransmitterReader = nullptr;
		DataReader* SignalReader      = nullptr;

		FSubscriberHandlers Handlers;
		std::atomic<std::uint64_t> Received{ 0 };

		TTopicListener<AircraftState>    AircraftListener;
		TTopicListener<FireEvent>        FireListener;
		TTopicListener<DetonationEvent>  DetonationListener;
		TTopicListener<EmissionSnapshot> EmissionListener;
		TTopicListener<TransmitterState> TransmitterListener;
		TTopicListener<SignalEvent>      SignalListener;

		bool Init(std::uint32_t DomainId, FSubscriberHandlers InHandlers)
		{
			Handlers = std::move(InHandlers);
			AircraftListener   .Handler = &Handlers.OnAircraftState;    AircraftListener   .Counter = &Received;
			FireListener       .Handler = &Handlers.OnFireEvent;        FireListener       .Counter = &Received;
			DetonationListener .Handler = &Handlers.OnDetonationEvent;  DetonationListener .Counter = &Received;
			EmissionListener   .Handler = &Handlers.OnEmissionSnapshot; EmissionListener   .Counter = &Received;
			TransmitterListener.Handler = &Handlers.OnTransmitterState; TransmitterListener.Counter = &Received;
			SignalListener     .Handler = &Handlers.OnSignalEvent;      SignalListener     .Counter = &Received;

			DomainParticipantFactory* Factory = DomainParticipantFactory::get_instance();
			if (!Factory) { return false; }

			Participant = Factory->create_participant(DomainId, PARTICIPANT_QOS_DEFAULT);
			if (!Participant) { return false; }

			AircraftStateType.register_type(Participant);
			FireEventType.register_type(Participant);
			DetonationEventType.register_type(Participant);
			EmissionType.register_type(Participant);
			TransmitterType.register_type(Participant);
			SignalType.register_type(Participant);

			Subscriber_ = Participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT);
			if (!Subscriber_) { return false; }

			auto MakeTopic = [&](const char* Name, TypeSupport& Type) -> Topic*
			{
				return Participant->create_topic(Name, Type.get_type_name(), TOPIC_QOS_DEFAULT);
			};

			AircraftTopic    = MakeTopic("clearance/aircraft/state",    AircraftStateType);
			FireTopic        = MakeTopic("clearance/weapons/fire",      FireEventType);
			DetonationTopic  = MakeTopic("clearance/weapons/detonation",DetonationEventType);
			EmissionTopic    = MakeTopic("clearance/radar/emission",    EmissionType);
			TransmitterTopic = MakeTopic("clearance/radio/transmitter", TransmitterType);
			SignalTopic      = MakeTopic("clearance/radio/signal",      SignalType);

			DataReaderQos ReaderQos = DATAREADER_QOS_DEFAULT;
			ReaderQos.reliability().kind = BEST_EFFORT_RELIABILITY_QOS;

			auto MakeReader = [&](Topic* T, DataReaderListener* L) -> DataReader*
			{
				return Subscriber_->create_datareader(T, ReaderQos, L);
			};

			AircraftReader    = MakeReader(AircraftTopic,    &AircraftListener);
			FireReader        = MakeReader(FireTopic,        &FireListener);
			DetonationReader  = MakeReader(DetonationTopic,  &DetonationListener);
			EmissionReader    = MakeReader(EmissionTopic,    &EmissionListener);
			TransmitterReader = MakeReader(TransmitterTopic, &TransmitterListener);
			SignalReader      = MakeReader(SignalTopic,      &SignalListener);

			return AircraftReader && FireReader && DetonationReader
			    && EmissionReader && TransmitterReader && SignalReader;
		}

		~FClearanceSubscriberImpl()
		{
			if (!Participant) { return; }
			Participant->delete_contained_entities();
			DomainParticipantFactory::get_instance()->delete_participant(Participant);
			Participant = nullptr;
		}
	};

	std::unique_ptr<FClearanceSubscriber> FClearanceSubscriber::Create(std::uint32_t DomainId, FSubscriberHandlers Handlers)
	{
		std::unique_ptr<FClearanceSubscriber> Instance(new FClearanceSubscriber());
		if (!Instance->Impl->Init(DomainId, std::move(Handlers))) { return nullptr; }
		return Instance;
	}

	FClearanceSubscriber::FClearanceSubscriber()
		: Impl(std::make_unique<FClearanceSubscriberImpl>())
	{}

	FClearanceSubscriber::~FClearanceSubscriber() = default;

	std::uint64_t FClearanceSubscriber::GetTotalReceivedCount() const
	{
		return Impl->Received.load(std::memory_order_relaxed);
	}
}
