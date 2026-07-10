// ============================================================================
// ClearanceDDSSubscriber.h - CLEARANCE's DDS subscriber API.
//
// Companion to FClearancePublisher. One FClearanceSubscriber owns a separate
// DomainParticipant, a Subscriber, and one DataReader per topic. Each Reader
// has a listener callback that invokes the user-supplied `OnSample` handler
// when new samples arrive. Handler is called on the DDS transport thread so
// keep it lightweight - copy the sample and post to your own queue if you
// need to do work. - TripleA
// ============================================================================

#pragma once

#include "ClearanceDDS/ClearanceDDSSanity.h"    // CLEARANCEDDS_API macro block
#include "AirspaceTelemetry.hpp"                // POD topic data types

#include <cstdint>
#include <functional>
#include <memory>

namespace ClearanceDDS
{
	class FClearanceSubscriberImpl;

	// Callbacks the caller supplies. Any handler can be nullptr - unmatched
	// topics are subscribed to anyway (samples get dropped in the reader). - TripleA
	struct FSubscriberHandlers
	{
		std::function<void(const AircraftState&)>    OnAircraftState;
		std::function<void(const FireEvent&)>        OnFireEvent;
		std::function<void(const DetonationEvent&)>  OnDetonationEvent;
		std::function<void(const EmissionSnapshot&)> OnEmissionSnapshot;
		std::function<void(const TransmitterState&)> OnTransmitterState;
		std::function<void(const SignalEvent&)>      OnSignalEvent;
	};

	class CLEARANCEDDS_API FClearanceSubscriber
	{
	public:
		// Create participant + all six readers on the given DDS domain. Match
		// the domain the publisher is running on (default 0). - TripleA
		static std::unique_ptr<FClearanceSubscriber> Create(std::uint32_t DomainId, FSubscriberHandlers Handlers);
		~FClearanceSubscriber();

		FClearanceSubscriber(const FClearanceSubscriber&) = delete;
		FClearanceSubscriber& operator=(const FClearanceSubscriber&) = delete;

		// Total samples successfully received on any reader since creation.
		std::uint64_t GetTotalReceivedCount() const;

	private:
		FClearanceSubscriber();
		std::unique_ptr<FClearanceSubscriberImpl> Impl;
	};
}
