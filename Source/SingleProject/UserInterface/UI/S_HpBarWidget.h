// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/UI/S_UserWidget.h"
#include "S_HpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_HpBarWidget : public US_UserWidget
{
	GENERATED_BODY()
	
public:
	US_HpBarWidget(const FObjectInitializer& ObjectInitializer);

	void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PbHpBar;

	UPROPERTY()
	float MaxHp;
};
