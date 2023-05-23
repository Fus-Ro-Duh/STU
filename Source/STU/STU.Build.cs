// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class STU : ModuleRules
{
	public STU(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Niagara",
			"PhysicsCore",
			"GameplayTasks",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] 
		
		{
			"STU/Public/Dev", 
			"STU/Public/Player", 
			"STU/Public/Weapon", 
			"STU/Public/Components",
			"STU/Public/UI",
            "STU/Public/Pickups",
            "STU/Public/Animations",
            "STU/Public/AI",
            "STU/Public/AI/Tasks",
            "STU/Public/AI/Services",
            "STU/Public/AI/Decorators",
            "STU/Public/AI/Contexts"
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
