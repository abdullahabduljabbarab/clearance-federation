// Proof-of-life smoke test for the Fast DDS integration. Verifies the SDK
// links against the module, the DLLs load at runtime, and a DomainParticipant
// can be created + destroyed on the default domain. Called from the module's
// startup path in dev builds - if it fires cleanly, the third-party wiring
// is good and we can move on to the real publisher / subscriber code.
// - TripleA

#pragma once

// Portable DLL export macro. Same defensive block as ClearanceDIS - works
// under Unreal Build Tool (which auto-defines the macro) and standalone
// builds (falls back to __declspec / __attribute__ visibility). - TripleA
#ifndef CLEARANCEDDS_API
	#if defined(_MSC_VER)
		#ifdef CLEARANCEDDS_BUILDING
			#define CLEARANCEDDS_API __declspec(dllexport)
		#else
			#define CLEARANCEDDS_API __declspec(dllimport)
		#endif
	#elif defined(__GNUC__) || defined(__clang__)
		#define CLEARANCEDDS_API __attribute__((visibility("default")))
	#else
		#define CLEARANCEDDS_API
	#endif
#endif

namespace ClearanceDDS
{
	// Creates a DomainParticipant on the default domain, checks it's valid,
	// then destroys it. Returns true on success. If this returns false, the
	// SDK failed to initialise - check FASTDDS_HOME + DLL search path. - TripleA
	CLEARANCEDDS_API bool RunSanityCheck();
}
