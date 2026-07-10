// Fast DDS proof-of-life. Creates + destroys a DomainParticipant on the
// default domain to smoke-test the whole third-party dependency chain -
// headers found, libs linked, DLLs discoverable at runtime, no ABI drift.
// If this fires cleanly the rest of the DDS integration can build on top.
// - TripleA

#include "ClearanceDDS/ClearanceDDSSanity.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/qos/DomainParticipantQos.hpp>

namespace ClearanceDDS
{
	bool RunSanityCheck()
	{
		using namespace eprosima::fastdds::dds;

		DomainParticipantFactory* Factory = DomainParticipantFactory::get_instance();
		if (Factory == nullptr) { return false; }

		DomainParticipant* Participant = Factory->create_participant(
			/*DomainId*/ 0,
			PARTICIPANT_QOS_DEFAULT);
		if (Participant == nullptr) { return false; }

		const bool bValid = Participant->is_enabled();
		Factory->delete_participant(Participant);
		return bValid;
	}
}
