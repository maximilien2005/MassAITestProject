// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MassAITestProject : ModuleRules
{
	public MassAITestProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",

			"HeadMountedDisplay",
			"MassEntity",
			"MassCommon",
			"MassNavigation",
			"MassMovement",
			"NavigationSystem",
			"AIModule",
			"MassAIBehavior",
			"StateTreeModule",
			"GameplayTags",
			"SmartObjectsModule",
			"MassSmartObjects",
			"MassSignals",
			"MassRepresentation",
			"MassLOD",
			"AnimToTexture",
			"WorldResources",
			"Kismet"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MassAITestProject",
			"MassAITestProject/Variant_Platforming",
			"MassAITestProject/Variant_Platforming/Animation",
			"MassAITestProject/Variant_Combat",
			"MassAITestProject/Variant_Combat/AI",
			"MassAITestProject/Variant_Combat/Animation",
			"MassAITestProject/Variant_Combat/Gameplay",
			"MassAITestProject/Variant_Combat/Interfaces",
			"MassAITestProject/Variant_Combat/UI",
			"MassAITestProject/Variant_SideScrolling",
			"MassAITestProject/Variant_SideScrolling/AI",
			"MassAITestProject/Variant_SideScrolling/Gameplay",
			"MassAITestProject/Variant_SideScrolling/Interfaces",
			"MassAITestProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
