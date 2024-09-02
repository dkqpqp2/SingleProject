// Fill out your copyright notice in the Description page of Project Settings.


#include "S_AIHpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interfaces/S_EnemyWidgetInterface.h"

US_AIHpBarWidget::US_AIHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void US_AIHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PbEnemyHpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbEnemyHpBar")));
	ensure(PbEnemyHpBar);

	IS_EnemyWidgetInterface* EnemyWidget = Cast<IS_EnemyWidgetInterface>(OwningActor);
	if (EnemyWidget)
	{
		EnemyWidget->SetupEnemyWidget(this);
	}
}

void US_AIHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);
	if (PbEnemyHpBar)
	{
		PbEnemyHpBar->SetPercent(NewCurrentHp / MaxHp);
	}
}


