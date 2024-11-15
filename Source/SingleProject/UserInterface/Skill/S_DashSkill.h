// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_DashSkill.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_DashSkill : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> DashIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> CooldownProgressBar;

	FTimerHandle CooldownTimerHandle;

	float CurrentCooldownTime;
	float MaxCooldownTime;
	
};
