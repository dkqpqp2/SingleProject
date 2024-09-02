// Fill out your copyright notice in the Description page of Project Settings.


#include "S_AIWidgetComponent.h"
#include "Enemy/UI/S_AIUserWidget.h"

void US_AIWidgetComponent::InitWidget()
{
	Super::InitWidget();

	US_AIUserWidget* AIWidget = Cast<US_AIUserWidget>(GetWidget());
	if (AIWidget)
	{
		AIWidget->SetOwningActor(GetOwner());
	}

}
