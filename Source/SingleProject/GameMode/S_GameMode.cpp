// Fill out your copyright notice in the Description page of Project Settings.


#include "S_GameMode.h"

AS_GameMode::AS_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerCharacterClassRef(TEXT("/Game/Character/Blueprints/BPS_CharacterPlayer.BPS_CharacterPlayer_C"));
	if (PlayerCharacterClassRef.Class)
	{
		DefaultPawnClass = PlayerCharacterClassRef.Class;
	}
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/SingleProject.S_PlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
