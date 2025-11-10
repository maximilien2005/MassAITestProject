// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MassEntityCourCPP : ModuleRules
{
	public MassEntityCourCPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",

            "HeadMountedDisplay",
			"MassEntity",
			"MassCommon",
			"MassMovement",
			"MassNavigation",
			"MassAIBehavior",
			"StateTreeModule",
			"MassRepresentation",
			"MassLOD",
			"GameplayTags"
    });


        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[] {
			"MassEntityCourCPP" 
		});

       
    }
}
