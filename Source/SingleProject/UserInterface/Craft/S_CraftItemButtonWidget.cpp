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

}

void US_CraftItemButtonWidget::SetupButton(const FName& NewItemID, const FText& ItemName)
{
	ItemID = NewItemID;
	if (ItemNameText)
	{
		ItemNameText->SetText(ItemName);
		//FString LogMessage = FString::Printf(TEXT("Name : %s, ID : %s"), *ItemName.ToString(), *NewItemID.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, LogMessage);
	}
}



void US_CraftItemButtonWidget::OnItemButtonClicked()
{
	AS_PlayerController* PlayerController = Cast<AS_PlayerController>(GetOwningPlayer());
	if (PlayerController)
	{
		AS_HUD* S_HUD = Cast<AS_HUD>(PlayerController->GetHUD());
		if (S_HUD)
		{
			US_CraftingWidget* CraftingWidget = S_HUD->GetCraftingWidget();
			if (CraftingWidget)
			{
				CraftingWidget->OnItemClicked(ItemID);
				FString LogMessage = FString::Printf(TEXT("ItemID : %s"), *ItemID.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, LogMessage);
			}
		}
	}
}
