// Fill out your copyright notice in the Description page of Project Settings.


#include "S_HUD.h"

#include "QuickSlot/S_QuickSlotPanel.h"
#include "Skill/S_SkillPanel.h"
#include "UserInterface/S_MainMenu.h"
#include "UserInterface/Interaction/S_InteractionWidget.h"
#include "UserInterface/Equipment/S_EquipmentPanel.h"
#include "UserInterface/Craft/S_CraftingWidget.h"
#include "UserInterface/NewCraft/S_NewCraftPanel.h"
#include "UserInterface/Skill/S_SkillPanel.h"

AS_HUD::AS_HUD()
{
	
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

	if (NewCraftWidgetClass)
	{
		NewCraftPanelWidget = CreateWidget<US_NewCraftPanel>(GetWorld(), NewCraftWidgetClass);
		NewCraftPanelWidget->AddToViewport();
		NewCraftPanelWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if(SkillPanelWidgetClass)
	{
		SkillPanelWidget = CreateWidget<US_SkillPanel>(GetWorld(), SkillPanelWidgetClass);
		SkillPanelWidget->AddToViewport();
		SkillPanelWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if(QuickSlotPanelWidgetClass)
	{
		QuickSlotPanelWidget = CreateWidget<US_QuickSlotPanel>(GetWorld(), QuickSlotPanelWidgetClass);
		QuickSlotPanelWidget->AddToViewport(-1);
		QuickSlotPanelWidget->SetVisibility(ESlateVisibility::Visible);
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
	if (!bIsCraftVisible && !bIsSkillMenuVisible)
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
}

void AS_HUD::DisplayCraft()
{
	if (NewCraftPanelWidget)
	{
		bIsCraftVisible = true;
		NewCraftPanelWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AS_HUD::HideCraft()
{
	if (NewCraftPanelWidget)
	{
		bIsCraftVisible = false;
		NewCraftPanelWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AS_HUD::ToggleCraft()
{
	if (!bIsMenuVisible && !bIsSkillMenuVisible)
	{
		if (bIsCraftVisible)
		{
			HideCraft();
			const FInputModeGameOnly InputMode;
			GetOwningPlayerController()->SetInputMode(InputMode);
			GetOwningPlayerController()->SetShowMouseCursor(false);
		}
		else
		{
			DisplayCraft();
			const FInputModeGameAndUI InputMode;
			GetOwningPlayerController()->SetInputMode(InputMode);
			GetOwningPlayerController()->SetShowMouseCursor(true);
		}
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

void AS_HUD::ShowSkillPanel()
{
	if(SkillPanelWidget)
	{
		bIsSkillMenuVisible = true;
		SkillPanelWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AS_HUD::HideSkillPanel()
{
	if(SkillPanelWidget)
	{
		bIsSkillMenuVisible = false;
		SkillPanelWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AS_HUD::ToggleSkillMenu()
{
	if (!bIsMenuVisible && !bIsCraftVisible)
	{
		if (bIsSkillMenuVisible)
		{
			HideSkillPanel();
			const FInputModeGameOnly InputMode;
			GetOwningPlayerController()->SetInputMode(InputMode);
			GetOwningPlayerController()->SetShowMouseCursor(false);
		}
		else
		{
			ShowSkillPanel();
			const FInputModeGameAndUI InputMode;
			GetOwningPlayerController()->SetInputMode(InputMode);
			GetOwningPlayerController()->SetShowMouseCursor(true);
		}
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


