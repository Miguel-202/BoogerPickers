// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheRizzard : ModuleRules
{
	public TheRizzard(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Niagara", "UMG", "AIModule", "NavigationSystem" });
	}
}
