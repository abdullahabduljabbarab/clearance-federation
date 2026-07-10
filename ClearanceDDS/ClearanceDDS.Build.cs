using System;
using System.IO;
using UnrealBuildTool;

// Standalone DDS pub/sub module. Wraps eProsima Fast DDS - the C++ native
// implementation of the OMG Data Distribution Service standard - with a
// clean pure-C++ API mirroring the ClearanceDIS module. Same isolation
// discipline: POD input structs, free functions, thin Unreal-side adapter
// in ClearanceSim on top. The public API stays engine-free so the module
// could drop into a Unity project, headless federate, or ROS 2 bridge.
//
// Fast DDS is the C++ middleware NEW defence systems build sensor fusion
// on (Tempest / FCAS combat cloud, FACE-standard avionics, autonomous
// wingmen). Pairing DDS alongside our DIS legacy interop is the "past +
// future" portfolio flex - table-stakes for BAE / Leonardo / MBDA. - TripleA
public class ClearanceDDS : ModuleRules
{
	public ClearanceDDS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
		});

		// Fast DDS SDK location. Defaults to the standard eProsima install
		// path; overridable via FASTDDS_HOME env var so a different dev
		// machine can point at a different install. - TripleA
		string FastDdsRoot = Environment.GetEnvironmentVariable("FASTDDS_HOME");
		if (string.IsNullOrEmpty(FastDdsRoot))
		{
			FastDdsRoot = @"C:\Program Files\eProsima\fastdds 3.6.1.0";
		}

		if (!Directory.Exists(FastDdsRoot))
		{
			throw new BuildException(
				"Fast DDS SDK not found. Install from https://www.eprosima.com/ " +
				"(default location: 'C:\\Program Files\\eProsima\\fastdds 3.6.1.0') " +
				"or set the FASTDDS_HOME environment variable.");
		}

		string IncludeDir = Path.Combine(FastDdsRoot, "include");
		string LibDir     = Path.Combine(FastDdsRoot, "lib");
		string BinDir     = Path.Combine(FastDdsRoot, "bin");

		// Treat Fast DDS headers as "system" includes so UE's strict
		// warnings-as-errors doesn't reject the SDK for MSVC C4668
		// (undefined macro like __APPLE__ treated as 0). - TripleA
		PublicSystemIncludePaths.Add(IncludeDir);

		// fastddsgen output for AirspaceTelemetry.idl. The generated header
		// AirspaceTelemetry.hpp defines the POD data types (AircraftState,
		// FireEvent, ...) that consumers hand to the publisher API - so its
		// folder is exposed as a public include path. Sits under Private/
		// only because fastddsgen writes it there and shouldn't be hand-
		// edited; not a Private/Public boundary violation, it's a build-
		// output convention. - TripleA
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Private", "Generated"));

		// Silence the specific warnings the Fast DDS headers trip on MSVC.
		// C4668 = undefined macro treated as 0 (Apple / FreeBSD / VXWORKS
		// build-target guards). C4265 = base class without virtual dtor. - TripleA
		PublicDefinitions.Add("__INTERNALDEBUG=0");
		PublicDefinitions.Add("_INTERNALDEBUG=0");

		// Fast DDS static-linked. Was DLL-linked initially but hit a cross-DLL
		// STL heap mismatch on Windows: fastdds-3.6.dll allocates an
		// std::vector inside its type-registration path, ClearanceDDS.dll's
		// operator delete (routed through UE's PerModuleInline FMemory) then
		// tries to free it against UE's heap - access violation. Static
		// linking pulls Fast DDS + FastCDR into UnrealEditor-ClearanceDDS.dll
		// directly so there's a single heap and no cross-boundary STL. - TripleA

		// Link against release-config .lib variants. UE Development / Shipping
		// both build with MSVC /MD runtime which matches these .lib files.
		// Debug (fastddsd-3.6.lib) exists in the same folder if UE debug
		// config ever needs it. - TripleA
		PublicAdditionalLibraries.AddRange(new string[]
		{
			Path.Combine(LibDir, "libfastdds-3.6.lib"),          // static
			Path.Combine(LibDir, "libfastcdr-2.3.lib"),          // static
			Path.Combine(LibDir, "foonathan_memory-0.7.4.lib"),  // static already
			// OpenSSL - static-linked Fast DDS pulls in its security transform
			// code (AESGCMGMAC) even when security is disabled at runtime; the
			// linker still needs to resolve EVP_* symbols. libcrypto+libssl
			// static libs are shipped in the eProsima SDK's VC/x64/MD folder. - TripleA
			Path.Combine(LibDir, "VC", "x64", "MD", "libcrypto.lib"),
			Path.Combine(LibDir, "VC", "x64", "MD", "libssl.lib")
		});

		// Static linking eliminates the DLL runtime dep on Fast DDS + FastCDR
		// + Foonathan Memory. OpenSSL DLLs still get bundled in case Fast DDS
		// security codepaths reach for libcrypto/libssl at runtime (default
		// config has security off, but the linker still pulls the symbol
		// references so the DLLs need to be discoverable). - TripleA
		string[] RuntimeDlls =
		{
			"libcrypto-3-x64.dll",
			"libssl-3-x64.dll"
		};
		foreach (string Dll in RuntimeDlls)
		{
			string SrcPath = Path.Combine(BinDir, Dll);
			RuntimeDependencies.Add("$(BinaryOutputDir)/" + Dll, SrcPath);
		}

		// Static Fast DDS transitively pulls in Windows sockets + threading. - TripleA
		PublicSystemLibraries.AddRange(new string[]
		{
			"ws2_32.lib",
			"iphlpapi.lib",
			"shlwapi.lib"
		});

		// Fast DDS headers use exceptions internally (OMG standard requires
		// throw semantics for RTI failures). UE modules disable exceptions
		// by default; enable them for this module so the SDK headers parse. - TripleA
		bEnableExceptions = true;

		// Silence the "not a preferred VS version" chatter without changing
		// the toolchain - Fast DDS builds cleanly against VS2022/2026 MSVC. - TripleA
		bUseUnity = false;
	}
}
