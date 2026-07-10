// Portable DLL export macro for the ClearanceRTI module. Under Unreal Build
// Tool the macro is set to __declspec(dllexport) when the module is being
// compiled and __declspec(dllimport) when a downstream module includes the
// public headers. Also works for standalone builds without UBT. Same shape
// as ClearanceDIS / ClearanceDDS. - TripleA

#pragma once

#ifndef CLEARANCERTI_API
	#if defined(_MSC_VER)
		#ifdef CLEARANCERTI_BUILDING
			#define CLEARANCERTI_API __declspec(dllexport)
		#else
			#define CLEARANCERTI_API __declspec(dllimport)
		#endif
	#elif defined(__GNUC__) || defined(__clang__)
		#define CLEARANCERTI_API __attribute__((visibility("default")))
	#else
		#define CLEARANCERTI_API
	#endif
#endif
