// Fill out your copyright notice in the Description page of Project Settings.


#include "S_GameInstance.h"

#include "Kismet/GameplayStatics.h"

US_GameInstance* US_GameInstance::Get(const UObject* InWorldContext)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(InWorldContext);
	US_GameInstance* SGameInstance = Cast<US_GameInstance>(GameInstance);; 
	return SGameInstance;
}