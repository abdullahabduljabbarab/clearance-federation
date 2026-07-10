// Standalone DDS pub/sub module bootstrap. Wraps eProsima Fast DDS. No
// runtime state at module level - each publisher / subscriber owns its
// own participant, topic, and datawriter/reader lifecycle. - TripleA

#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FDefaultModuleImpl, ClearanceDDS)
