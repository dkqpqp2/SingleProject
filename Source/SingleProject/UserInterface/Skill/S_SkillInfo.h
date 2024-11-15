// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_SkillInfo.generated.h"


struct FSkillData;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_SkillInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetSkillData(const FSkillData& InSkillData);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> SkillIcon;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillName;
};
