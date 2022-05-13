// Copyright Epic Games, Inc. All Rights Reserved.

#include "ComboCoinPTRlGameMode.h"
#include "ComboCoinPTRlCharacter.h"
#include "UObject/ConstructorHelpers.h"

AComboCoinPTRlGameMode::AComboCoinPTRlGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
