// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FG22_EndlessRunner : ModuleRules
{
	public FG22_EndlessRunner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG" });
	}
}
