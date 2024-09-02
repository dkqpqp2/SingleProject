// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Actor)
	TObjectPtr<AActor> OwningActor;
	
};
