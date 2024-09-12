// Fill out your copyright notice in the Description page of Project Settings.


#include "S_HUD.h"
#include "UserInterface/S_MainMenu.h"
#include "UserInterface/Interaction/S_InteractionWidget.h"
#include "UserInterface/Equipment/S_EquipmentPanel.h"
#include "UserInterface/Craft/S_CraftingWidget.h"

AS_HUD::AS_HUD()
{
	if (CraftingWidgetClass)
	{
		CraftingWidget = CreateWidget<US_CraftingWidget>(GetOwningPlayerController(), CraftingWidgetClass);
		if (CraftingWidget)
		{
			CraftingWidget->AddToViewport();
		}
	}
}

void AS_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<US_MainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<US_InteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (CrosshairWidgetClass)
	{
		CrosshairWidget = CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass);
		CrosshairWidget->AddToViewport();
		CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (EquipmentWidgetClass)
	{
		EquipmentWidget = CreateWidget<US_EquipmentPanel>(GetWorld(), EquipmentWidgetClass);
		EquipmentWidget->AddToViewport();
		EquipmentWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (CraftingWidgetClass)
	{
		CraftingWidget = CreateWidget<US_CraftingWidget>(GetWorld(), CraftingWidgetClass);
		CraftingWidget->AddToViewport();
		CraftingWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

}

void AS_HUD::DisplayMenu()
{
	if (MainMenuWidget)
	{
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
	
}

void AS_HUD::HideMenu()
{
	if (MainMenuWidget)
	{
		bIsMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	
}

void AS_HUD::ToggleMenu()
{
	
	if (bIsMenuVisible)
	{
		HideMenu();

		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		DisplayMenu();
		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void AS_HUD::ShowCrosshair()
{
	if (CrosshairWidget)
	{
		CrosshairWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AS_HUD::HideCrosshair()
{
	if (CrosshairWidget)
	{
		CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AS_HUD::ShowInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AS_HUD::HideInteractionWidget() const
{
	if (MainMenuWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AS_HUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}
		InteractionWidget->UpdateWidget(InteractableData);
	}
}

US_CraftingWidget* AS_HUD::GetCraftingWidget() const
{
	return CraftingWidget;
}


