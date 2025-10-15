// Copyright Epic Games, Inc. All Rights Reserved.

#include "Extraordinaria_UIGameMode.h"
#include "Extraordinaria_UICharacter.h"
#include "UObject/ConstructorHelpers.h"

AExtraordinaria_UIGameMode::AExtraordinaria_UIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
