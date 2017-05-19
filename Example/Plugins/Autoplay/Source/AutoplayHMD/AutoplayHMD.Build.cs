using UnrealBuildTool;
using System.IO;

public class AutoplayHMD : ModuleRules
{
	public AutoplayHMD(TargetInfo Target)
	{
		PrivateIncludePaths.AddRange(new string[] { "AutoplayHMD/Private" });
		PublicIncludePaths.AddRange(new string[] { "AutoplayHMD/Public" });

		PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Autoplay" });
		PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}