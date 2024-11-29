// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Snowed_In : ModuleRules
{
	public Snowed_In(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" });
    }
}
