// Standalone RTI Connext DDS pub/sub module bootstrap. Sibling to
// ClearanceDDS but bound against RTI's commercial Connext runtime. No
// runtime state at module level - each publisher / subscriber owns its
// own participant, topic, and datawriter/reader lifecycle. - TripleA

#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FDefaultModuleImpl, ClearanceRTI)
