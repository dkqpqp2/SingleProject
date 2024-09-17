// Fill out your copyright notice in the Description page of Project Settings.


#include "S_CraftItemButtonWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SingleProject/UserInterface/Craft/S_CraftingWidget.h"
#include "SingleProject/UserInterface/S_HUD.h"
#include "SingleProject/PlayerController/S_PlayerController.h"

void US_CraftItemButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &US_CraftItemButtonWidget::OnItemButtonClicked);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald,TEXT("ItemButton is null"));
	}

}

void US_CraftItemButtonWidget::SetupButton(const FName& NewItemID, const FText& ItemName)
{
	ItemID = NewItemID;
	if (ItemNameText)
	{
		ItemNameText->SetText(ItemName);
	}
}



void US_CraftItemButtonWidget::OnItemButtonClicked()
{
	OnCraftItemButtonClicked.ExecuteIfBound(ItemID);
}
