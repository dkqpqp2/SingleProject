// Fill out your copyright notice in the Description page of Project Settings.


#include "S_PlayerController.h"

void AS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
