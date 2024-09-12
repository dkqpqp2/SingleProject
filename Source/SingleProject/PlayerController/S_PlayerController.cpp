// Fill out your copyright notice in the Description page of Project Settings.


#include "S_PlayerController.h"
#include "SingleProject/UserInterface/S_HUD.h"

AS_PlayerController::AS_PlayerController()
{
	HUD = CreateDefaultSubobject<AS_HUD>(TEXT("HUD"));
}

void AS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
