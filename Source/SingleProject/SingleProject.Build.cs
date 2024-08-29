// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class SingleProject : ModuleRules
{
	public SingleProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { "SingleProject"});

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG",
            "Niagara",
            "NavigationSystem",
            "AIModule",
            "GamePlayTasks",
            "SlateCore",
            "Slate",
            "Paper2D"

        });
	}
}
