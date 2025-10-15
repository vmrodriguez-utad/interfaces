// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Extraordinaria_UI : ModuleRules
{
	public Extraordinaria_UI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Slate", "SlateCore"
		});
	}
}
