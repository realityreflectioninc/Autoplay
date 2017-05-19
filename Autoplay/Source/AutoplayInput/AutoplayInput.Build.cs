using UnrealBuildTool;
using System.IO;

public class AutoplayInput : ModuleRules
{
	public AutoplayInput(TargetInfo Target)
	{
		PrivateIncludePaths.AddRange(new string[] { "AutoplayInput/Private" });
		PublicIncludePaths.AddRange(new string[] { "AutoplayInput/Public" });

		PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "Engine", "InputCore", "InputDevice", "Autoplay", "HeadMountedDisplay" });
		PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}