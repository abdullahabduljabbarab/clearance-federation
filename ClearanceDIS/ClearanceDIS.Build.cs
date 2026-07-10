using UnrealBuildTool;

// Standalone DIS wire-format module. Public API is pure C++ - no Unreal types,
// no UObject, no FName / FVector / TArray. The point is that the wire format
// implementation is decoupled from the render layer, so this module could be
// linked into a headless federate, a Unity build, a C++ command-line tool, or
// any transport (UDP / TCP / HLA bridge). ClearanceSim adapts its Unreal-side
// aircraft / radio / voice structs at the module boundary and calls in. - TripleA
public class ClearanceDIS : ModuleRules
{
	public ClearanceDIS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		// Deliberately minimal - Core only for the module-loading boilerplate.
		// The wire format implementation uses <cstdint> / <vector> / <string>
		// from the standard library and nothing else. - TripleA
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
		});
	}
}
