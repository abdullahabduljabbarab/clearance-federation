// Portable DLL export macro for the ClearanceHLA module. Same shape as
// ClearanceDIS / ClearanceDDS / ClearanceRTI. - TripleA

#pragma once

#ifndef CLEARANCEHLA_API
	#if defined(_MSC_VER)
		#ifdef CLEARANCEHLA_BUILDING
			#define CLEARANCEHLA_API __declspec(dllexport)
		#else
			#define CLEARANCEHLA_API __declspec(dllimport)
		#endif
	#elif defined(__GNUC__) || defined(__clang__)
		#define CLEARANCEHLA_API __attribute__((visibility("default")))
	#else
		#define CLEARANCEHLA_API
	#endif
#endif
