// Fill out your copyright notice in the Description page of Project Settings.


#include "S_CraftButtonWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/S_InventoryComponent.h"
#include "UserInterface/Craft/S_CraftingWidget.h"
#include "UserInterface/S_HUD.h"
#include "PlayerController/S_PlayerController.h"

#include "GameFramework/Character.h"

void US_CraftButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CraftButton)
	{
		CraftButton->OnClicked.AddDynamic(this, &US_CraftButtonWidget::OnItemButtonClicked);
	}
}

void US_CraftButtonWidget::SetupButton(const FText& InText)
{
	CraftText->SetText(InText);
}

void US_CraftButtonWidget::OnItemButtonClicked()
{
	ACharacter* OwningPlayerCharacter = Cast<ACharacter>(GetOwningPlayerPawn());
	InventoryReference = OwningPlayerCharacter->FindComponentByClass<US_InventoryComponent>();
	if (!InventoryReference)
	{
		return;
	}

	if (CraftingWidget)
	{

		FName SelectedItemID = CraftingWidget->GetSeletItemButton();
		if (CraftingWidget->CachedItemDataMap.Contains(SelectedItemID))
		{
			const FItemData& ItemData = CraftingWidget->CachedItemDataMap[SelectedItemID];
			if (CraftingWidget->CanCraftItem(ItemData))
			{
				CraftingWidget->CraftItem(ItemData);
			}
		}
	}
}