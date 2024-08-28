// Fill out your copyright notice in the Description page of Project Settings.


#include "S_InventoryPanel.h"
#include "UserInterface/Inventory/S_InventoryPanel.h"
#include "UserInterface/Inventory/S_InventoryItemSlot.h"
#include "UserInterface/Inventory/S_ItemDragDropOperation.h"
#include "Components/S_InventoryComponent.h"
#include "Components/S_EquipmentComponent.h"
#include "Character/S_CharacterPlayer.h"
#include "Items/S_ItemBase.h"

#include "Components/TextBlock.h"
#include "Components/WrapBox.h"


void US_InventoryPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PlayerCharacter = Cast<AS_CharacterPlayer>(GetOwningPlayerPawn());
	if (PlayerCharacter)
	{
		InventoryReference = PlayerCharacter->GetInventory();
		if (InventoryReference)
		{
			InventoryReference->OnInventoryUpdated.AddUObject(this, &US_InventoryPanel::RefreshInventory);
			SetInfoText();
		}
	}
}

void US_InventoryPanel::SetInfoText() const
{
	const FString WeightInfoValue{
		FString::SanitizeFloat(InventoryReference->GetInventoryTotalWeight()) + "/"
		+ FString::SanitizeFloat(InventoryReference->GetWeightCapacity())
	};

	const FString CapacityInfoValue{
		FString::FromInt(InventoryReference->GetInventoryContents().Num()) + "/"
		+ FString::FromInt(InventoryReference->GetSlotsCapacity())
	};

	WeightInfo->SetText(FText::FromString(WeightInfoValue));
	CapacityInfo->SetText(FText::FromString(CapacityInfoValue));
}

void US_InventoryPanel::RefreshInventory()
{
	if (InventoryReference && InventorySlotClass)
	{
		InventoryWrapBox->ClearChildren();
		for (US_ItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
		{
			US_InventoryItemSlot* ItemSlot = CreateWidget<US_InventoryItemSlot>(this, InventorySlotClass);
			ItemSlot->SetItemReference(InventoryItem);

			InventoryWrapBox->AddChildToWrapBox(ItemSlot);
		}

		SetInfoText();
	}
}




bool US_InventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	const US_ItemDragDropOperation* ItemDragDropOperation = Cast<US_ItemDragDropOperation>(InOperation);

	if (ItemDragDropOperation->SourceItem && InventoryReference)
	{
		switch (ItemDragDropOperation->SourceItem->ItemType)
		{
		case EItemType::Weapon:
			ItemDragDropOperation->SourceItem->OwningEquipment->UnequipItem(ESlotName::Weapon, TEXT("WeaponSocket"));
			ItemDragDropOperation->SourceItem->OwningInventory->HandleAddItem(ItemDragDropOperation->SourceItem);
			break;
		case EItemType::Armor:
			ItemDragDropOperation->SourceItem->OwningEquipment->UnequipItem(ESlotName::Armor, TEXT("ArmorSocket"));
			ItemDragDropOperation->SourceItem->OwningInventory->HandleAddItem(ItemDragDropOperation->SourceItem);
			break;
		case EItemType::Helmet:
			ItemDragDropOperation->SourceItem->OwningEquipment->UnequipItem(ESlotName::Helmet, TEXT("HelmetSocket"));
			ItemDragDropOperation->SourceItem->OwningInventory->HandleAddItem(ItemDragDropOperation->SourceItem);
			break;
		case EItemType::Shield:
			ItemDragDropOperation->SourceItem->OwningEquipment->UnequipItem(ESlotName::Shield, TEXT("ShieldSocket"));
			ItemDragDropOperation->SourceItem->OwningInventory->HandleAddItem(ItemDragDropOperation->SourceItem);
			break;
		case EItemType::Boots:
			ItemDragDropOperation->SourceItem->OwningEquipment->UnequipItem(ESlotName::Boots, TEXT("BootsSocket"));
			ItemDragDropOperation->SourceItem->OwningInventory->HandleAddItem(ItemDragDropOperation->SourceItem);
			break;
		default:;
		}
		return true;
	}
	return false;
}
