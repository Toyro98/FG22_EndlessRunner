// Copyright Epic Games, Inc. All Rights Reserved.

#include "FG22_EndlessRunnerGameMode.h"
#include "FG22_EndlessRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFG22_EndlessRunnerGameMode::AFG22_EndlessRunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
