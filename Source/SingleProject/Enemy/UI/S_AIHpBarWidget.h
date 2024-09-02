// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/UI/S_AIUserWidget.h"
#include "S_AIHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_AIHpBarWidget : public US_AIUserWidget
{
	GENERATED_BODY()
public:
	US_AIHpBarWidget(const FObjectInitializer& ObjectInitializer);

	void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PbEnemyHpBar;

	UPROPERTY()
	float MaxHp;
};
