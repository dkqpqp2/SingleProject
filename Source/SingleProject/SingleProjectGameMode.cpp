// Copyright Epic Games, Inc. All Rights Reserved.

#include "SingleProjectGameMode.h"
#include "SingleProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASingleProjectGameMode::ASingleProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
