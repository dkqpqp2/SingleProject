// Fill out your copyright notice in the Description page of Project Settings.


#include "S_HpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interfaces/S_CharacterWidgetInterface.h"

US_HpBarWidget::US_HpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void US_HpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PbHpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
	ensure(PbHpBar);

	IS_CharacterWidgetInterface* CharacterWidget = Cast<IS_CharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}


void US_HpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);
	if (PbHpBar)
	{
		PbHpBar->SetPercent(NewCurrentHp / MaxHp);
	}
}

