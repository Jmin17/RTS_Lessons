// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RTS_Lessons : ModuleRules
{
	public RTS_Lessons(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject",
			"Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore",
			"UMG" }); 
    }
}
