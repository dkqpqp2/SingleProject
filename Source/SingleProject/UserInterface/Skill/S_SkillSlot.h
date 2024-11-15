// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_SkillSlot : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> SkillIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillText;
};
