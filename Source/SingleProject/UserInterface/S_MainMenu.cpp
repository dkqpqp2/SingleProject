// Fill out your copyright notice in the Description page of Project Settings.


#include "S_MainMenu.h"
#include "Character/S_CharacterPlayer.h"
#include "UserInterface/Inventory/S_ItemDragDropOperation.h"
#include "Items/S_ItemBase.h"

void US_MainMenu::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void US_MainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    PlayerCharacter = Cast<AS_CharacterPlayer>(GetOwningPlayerPawn());
}

bool US_MainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	const US_ItemDragDropOperation* ItemDragDrop = Cast<US_ItemDragDropOperation>(InOperation);
	if (PlayerCharacter && ItemDragDrop->SourceItem)
	{
		PlayerCharacter->DropItem(ItemDragDrop->SourceItem, ItemDragDrop->SourceItem->Quantity);
		return true;
	}
	return false;
}
