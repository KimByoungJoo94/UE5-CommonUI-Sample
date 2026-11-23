// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyCommonUI : ModuleRules
{
	public MyCommonUI(ReadOnlyTargetRules Target) : base(Target)
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
            "CommonUI"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"AssetRegistry", 
			"DeveloperSettings", 
			"GameplayTags", 
			"SlateCore", 
			"CommonInput" 
		});

		PublicIncludePaths.AddRange(new string[] {
			"MyCommonUI",
			"MyCommonUI/Variant_Platforming",
			"MyCommonUI/Variant_Platforming/Animation",
			"MyCommonUI/Variant_Combat",
			"MyCommonUI/Variant_Combat/AI",
			"MyCommonUI/Variant_Combat/Animation",
			"MyCommonUI/Variant_Combat/Gameplay",
			"MyCommonUI/Variant_Combat/Interfaces",
			"MyCommonUI/Variant_Combat/UI",
			"MyCommonUI/Variant_SideScrolling",
			"MyCommonUI/Variant_SideScrolling/AI",
			"MyCommonUI/Variant_SideScrolling/Gameplay",
			"MyCommonUI/Variant_SideScrolling/Interfaces",
			"MyCommonUI/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
