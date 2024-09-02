// Fill out your copyright notice in the Description page of Project Settings.


#include "S_WidgetComponent.h"
#include "UserInterface/UI/S_UserWidget.h"

void US_WidgetComponent::InitWidget()
{
	Super::InitWidget();

	US_UserWidget* S_UserWidget = Cast<US_UserWidget>(GetWidget());
	if (S_UserWidget)
	{
		S_UserWidget->SetOwningActor(GetOwner());
	}


}
