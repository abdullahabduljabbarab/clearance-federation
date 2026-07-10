using System;
using System.IO;
using UnrealBuildTool;

// Standalone RTI Connext DDS pub/sub module. Sibling to ClearanceDDS -
// same public-API shape, same IDL, same six topics, just bound against
// RTI's commercial Connext runtime instead of eProsima Fast DDS. The
// point isn't redundancy: RTI Connext is what BAE Warton's Tempest
// combat cloud, most Lockheed programmes, and the majority of tier-one
// defence primes actually deploy on. Having a working RTI adapter next
// to the Fast DDS one demonstrates familiarity with BOTH the open-
// source and the commercial DDS runtimes - table-stakes for a
// simulation-engineer conversation with anyone in the DDS market. - TripleA
public class ClearanceRTI : ModuleRules
{
	public ClearanceRTI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
		});

		// RTI Connext SDK location. Defaults to the standard install path
		// from the RTI Launcher installer; overridable via NDDSHOME env
		// var (RTI's own convention) so a different dev machine can
		// point at a different install. - TripleA
		string NddsHome = Environment.GetEnvironmentVariable("NDDSHOME");
		if (string.IsNullOrEmpty(NddsHome))
		{
			NddsHome = @"C:\Program Files\rti_connext_dds-7.7.0";
		}

		if (!Directory.Exists(NddsHome))
		{
			throw new BuildException(
				"RTI Connext DDS SDK not found. Install from https://www.rti.com/ " +
				"(default location: 'C:\\Program Files\\rti_connext_dds-7.7.0') " +
				"or set the NDDSHOME environment variable.");
		}

		string IncludeDir = Path.Combine(NddsHome, "include");
		string LibDir     = Path.Combine(NddsHome, "lib", "x64Win64VS2017");

		// Treat RTI headers as "system" includes so UE's warnings-as-errors
		// doesn't reject the SDK for MSVC C4668 / C4265 etc. Same reason
		// ClearanceDDS does it for Fast DDS. - TripleA
		PublicSystemIncludePaths.Add(IncludeDir);
		PublicSystemIncludePaths.Add(Path.Combine(IncludeDir, "ndds"));
		PublicSystemIncludePaths.Add(Path.Combine(IncludeDir, "ndds", "hpp"));

		// rtiddsgen output for AirspaceTelemetry.idl. Same IDL text file
		// as ClearanceDDS - both modules read from a shared spec, code-
		// gen just uses different tools (fastddsgen vs rtiddsgen) and
		// lands in the module's own Generated folder. - TripleA
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Private", "Generated"));

		// RTI static-link. Matches the pattern used for Fast DDS - single
		// heap in UnrealEditor-ClearanceRTI.dll, no cross-DLL STL boundary
		// where an RTI-allocated std::vector could get freed against UE's
		// FMemory. Static libs are the "z" suffix variants (e.g. nddscz.lib
		// = C API static, nddscpp2z.lib = Modern C++ API static,
		// nddscorez.lib = core static). Release-config CRT match. - TripleA
		PublicAdditionalLibraries.AddRange(new string[]
		{
			Path.Combine(LibDir, "nddscpp2z.lib"),   // Modern C++ (dds::dds.hpp) API
			Path.Combine(LibDir, "nddscz.lib"),      // C API (Modern C++ delegates here)
			Path.Combine(LibDir, "nddscorez.lib")    // Core (foundation for both)
		});

		// RTI required build defines for static-linked Modern C++ API on
		// Windows x64 VS2017 toolchain. NDDS_STATIC_LIBS switches header
		// visibility from dllimport to static-friendly. RTI_STATIC + the
		// platform macros are what the "-target" flag would set if we ran
		// rtiddsgen with the target flag; matching them here manually so
		// the headers pick the right code path. - TripleA
		PublicDefinitions.Add("RTI_STATIC");
		PublicDefinitions.Add("NDDS_STATIC_LIBS");
		PublicDefinitions.Add("RTI_WIN32");
		PublicDefinitions.Add("RTI_64BIT");
		// Never define RTI_UNIX - the SDK headers use `#if defined(RTI_UNIX)`
		// which is true regardless of value, so setting it to 0 still pulls
		// in Unix-only includes like <unistd.h>. - TripleA

		// PRIVATE (build-side only) - flips the generated user types from
		// nothing to __declspec(dllexport) so the constructors + destructors
		// of ClearanceRTI::WireHeader / AircraftState / ... land in
		// UnrealEditor-ClearanceRTI's exported symbol table. Without this
		// the generated .cpp defines them but the DLL's .lib import file
		// has no entry, and ClearanceSim fails to link. Consumers of the
		// header (other DLLs) get an empty NDDSUSERDllExport, which is
		// fine because MSVC will link against the .lib import file for
		// the same symbol name. - TripleA
		PrivateDefinitions.Add("NDDS_USER_DLL_EXPORT");

		// RTI static libs transitively pull in Windows sockets, threading,
		// timing, and version info. Same set the RTI-shipped example
		// makefiles link with for static builds. - TripleA
		PublicSystemLibraries.AddRange(new string[]
		{
			"ws2_32.lib",
			"iphlpapi.lib",
			"netapi32.lib",
			"advapi32.lib",
			"user32.lib",
			"winmm.lib",
			"version.lib"
		});

		// RTI headers use exceptions internally (dds::core::Error hierarchy).
		// UE modules disable exceptions by default; enable them here for
		// the same reason ClearanceDDS does. - TripleA
		bEnableExceptions = true;

		// Runtime type info required by the Modern C++ API (dds::topic::
		// topic_type_name resolution goes through typeid). - TripleA
		bUseRTTI = true;

		// Skip unity - RTI's Modern C++ headers pull a lot in and the
		// unity build occasionally hits internal-compiler edge cases on
		// heavyweight template output. Match Fast DDS's approach. - TripleA
		bUseUnity = false;
	}
}
