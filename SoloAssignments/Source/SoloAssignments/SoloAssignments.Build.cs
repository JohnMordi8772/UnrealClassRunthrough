// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SoloAssignments : ModuleRules
{
	public SoloAssignments(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
