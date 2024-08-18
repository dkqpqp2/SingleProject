// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "S_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API AS_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay()override;
	
};
