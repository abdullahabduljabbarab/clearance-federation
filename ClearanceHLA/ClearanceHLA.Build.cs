using System;
using System.IO;
using UnrealBuildTool;

// Standalone HLA (IEEE 1516-2010, "HLA Evolved") federate module. Fourth
// interoperability wire alongside DIS + Fast DDS + RTI Connext, and the
// portfolio piece that most legacy defence training rigs still run on -
// NATO federated exercises, MOD programme phases, US DoD FTX cycles.
// Bound against OpenRTI 0.10.0, the actively-maintained open-source
// IEEE 1516-2010 RTI - vendored under Plugins/ClearanceSim/ThirdParty/
// OpenRTI/ after being built from source with MSVC 2026 + CMake 4.3.
//
// Same isolation discipline as ClearanceDDS + ClearanceRTI:
// - POD input shapes hidden behind an FClearanceHLAFederate facade
// - RTI ambassador types (rti1516e::RTIambassador etc.) never leak
//   through the public API surface
// - Windows.h pollution from the RTI headers guarded by UE's third-
//   party include block wrappers
// - Adapter (UClearanceHLAEmitter) lives in ClearanceSim, not here,
//   so this module stays UE-free at the surface. - TripleA
public class ClearanceHLA : ModuleRules
{
	public ClearanceHLA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"Projects"        // for IPluginManager - used to resolve the vendored DLL path at runtime
		});

		// Vendored OpenRTI location. Absolute path relative to the plugin
		// root so no env var setup is needed on a fresh checkout - the
		// libs + headers + DLLs travel with the repo. See
		// ThirdParty/OpenRTI/README.md for the build recipe if the
		// vendored binaries need refreshing. - TripleA
		string OpenRtiRoot = Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "OpenRTI");
		OpenRtiRoot = Path.GetFullPath(OpenRtiRoot);

		if (!Directory.Exists(OpenRtiRoot))
		{
			throw new BuildException(
				"Vendored OpenRTI not found at '" + OpenRtiRoot + "'. " +
				"Build OpenRTI from source (see ThirdParty/OpenRTI/README.md) " +
				"and drop the outputs at the standard include/lib/bin layout.");
		}

		string IncludeDir = Path.Combine(OpenRtiRoot, "include", "rti1516e");
		string LibDir     = Path.Combine(OpenRtiRoot, "lib");
		string BinDir     = Path.Combine(OpenRtiRoot, "bin");

		// Treat OpenRTI headers as "system" so UE's warnings-as-errors
		// doesn't reject them (rti1516e uses c-style casts + deprecated
		// STL patterns in a few spots). Same pattern as ClearanceRTI. - TripleA
		PublicSystemIncludePaths.Add(IncludeDir);
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));

		// Link against the three OpenRTI import libraries:
		// - rti1516e.lib      : the RTIambassador + FederateAmbassador API
		// - fedtime1516e.lib  : LogicalTime factory + interval helpers
		// - OpenRTI.lib       : core runtime (transport, message dispatch,
		//                       server tree). rti1516e depends on this. - TripleA
		PublicAdditionalLibraries.AddRange(new string[]
		{
			Path.Combine(LibDir, "rti1516e.lib"),
			Path.Combine(LibDir, "fedtime1516e.lib"),
			Path.Combine(LibDir, "OpenRTI.lib")
		});

		// OpenRTI ships as DLLs (not fully static-linkable at this build
		// config). The DLLs need to be findable by the Windows loader when
		// ClearanceHLA.dll is loaded - Windows searches the LOADING PROCESS
		// dir (UnrealEditor.exe) NOT the loading DLL's dir, so dropping
		// them next to UnrealEditor-ClearanceHLA.dll isn't enough on its own.
		// Two-part fix:
		//   1. RuntimeDependencies makes UBT copy them to the module's
		//      Binaries dir so a packaged build ships them
		//   2. PublicDelayLoadDLLs + explicit FPlatformProcess::GetDllHandle
		//      in the module StartupModule loads them from the plugin's
		//      Binaries dir at runtime, sidestepping the loader search order
		// - TripleA
		string[] RuntimeDlls =
		{
			"librti1516e.dll",
			"libfedtime1516e.dll",
			"OpenRTI.dll"
		};
		foreach (string Dll in RuntimeDlls)
		{
			string SrcPath = Path.Combine(BinDir, Dll);
			RuntimeDependencies.Add("$(BinaryOutputDir)/" + Dll, SrcPath);
			PublicDelayLoadDLLs.Add(Dll);
		}

		// OpenRTI headers throw exceptions on RTI failures (federate
		// isn't licensed, federation not found, save-in-progress, ...).
		// UE modules disable exceptions by default; enable them here so
		// the ambassador facade can catch dds::core::Error's HLA
		// equivalents cleanly. - TripleA
		bEnableExceptions = true;

		// Modern C++ HLA headers use typeid at Handle resolution paths -
		// need RTTI too. - TripleA
		bUseRTTI = true;

		// Skip unity so the RTI header pollution never bleeds into
		// sibling TUs in the module (only one .cpp for now anyway). - TripleA
		bUseUnity = false;
	}
}
