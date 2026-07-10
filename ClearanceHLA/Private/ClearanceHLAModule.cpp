// Standalone HLA (IEEE 1516-2010) federate module bootstrap. Fourth
// interoperability wire alongside DIS + Fast DDS + RTI Connext.
//
// Loads the three vendored OpenRTI DLLs (librti1516e.dll,
// libfedtime1516e.dll, OpenRTI.dll) at module startup from the plugin's
// own Binaries directory. Marked as PublicDelayLoadDLLs in Build.cs so
// the Windows loader doesn't try to resolve them via its default search
// path (which doesn't include plugin dirs) - we do the load explicitly
// here where we can point at the right directory. - TripleA

#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"

class FClearanceHLAModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("ClearanceSim"));
		if (!Plugin.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("[ClearanceHLA] Could not resolve ClearanceSim plugin base dir - OpenRTI DLL load skipped"));
			return;
		}
		FString BinariesDir = FPaths::Combine(Plugin->GetBaseDir(), TEXT("Binaries"), TEXT("Win64"));
		BinariesDir = FPaths::ConvertRelativePathToFull(BinariesDir);

		// librti1516e.dll and libfedtime1516e.dll import each other -
		// circular DLL dependency, which the Windows loader can't resolve
		// via LoadLibrary with a full path. Push the Binaries dir onto the
		// DLL search path FIRST so the loader can look up either DLL by
		// name during resolution. Once we've loaded them the push is
		// no longer needed and we pop. - TripleA
		FPlatformProcess::PushDllDirectory(*BinariesDir);

		// Order matters: OpenRTI.dll first because rti1516e + fedtime1516e
		// both depend on it. Then librti1516e (fedtime imports it), then
		// fedtime (rti1516e imports it - but rti's already loaded so its
		// import of fedtime is deferred). - TripleA
		const TCHAR* DllNames[] =
		{
			TEXT("OpenRTI.dll"),
			TEXT("librti1516e.dll"),
			TEXT("libfedtime1516e.dll")
		};

		for (const TCHAR* Name : DllNames)
		{
			const FString FullPath = FPaths::Combine(BinariesDir, Name);
			void* Handle = FPlatformProcess::GetDllHandle(*FullPath);
			if (!Handle)
			{
				UE_LOG(LogTemp, Error, TEXT("[ClearanceHLA] Failed to load '%s' from '%s'"), Name, *BinariesDir);
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("[ClearanceHLA] Loaded '%s'"), Name);
				DllHandles.Add(Handle);
			}
		}

		FPlatformProcess::PopDllDirectory(*BinariesDir);
	}

	virtual void ShutdownModule() override
	{
		// Reverse-unload to respect the reverse dependency order. - TripleA
		for (int32 i = DllHandles.Num() - 1; i >= 0; --i)
		{
			FPlatformProcess::FreeDllHandle(DllHandles[i]);
		}
		DllHandles.Empty();
	}

private:
	TArray<void*> DllHandles;
};

IMPLEMENT_MODULE(FClearanceHLAModule, ClearanceHLA)
