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
		HandleItemDrop(ItemDragDropOperation->SourceItem);
		return true;
	}
	return false;
}


void US_InventoryPanel::HandleItemDrop(US_ItemBase* Item)
{
	if (!Item || !Item->OwningEquipment || !Item->OwningInventory)
	{
		return;
	}

	ESlotName SlotName;
	FString SocketName;
	switch (Item->ItemType)
	{
	case EItemType::Weapon:
		SlotName = ESlotName::Weapon;
		SocketName = TEXT("WeaponSocket");
		break;
	case EItemType::Armor:
		SlotName = ESlotName::Armor;
		SocketName = TEXT("ArmorSocket");
		break;
	case EItemType::Helmet:
		SlotName = ESlotName::Helmet;
		SocketName = TEXT("HelmetSocket");
		break;
	case EItemType::Shield:
		SlotName = ESlotName::Shield;
		SocketName = TEXT("ShieldSocket");
		break;
	case EItemType::Boots:
		SlotName = ESlotName::Boots;
		SocketName = TEXT("BootsSocket");
		break;
	default:
		return;
	}
	Item->OwningEquipment->UnequipItem(SlotName, *SocketName);
	Item->OwningInventory->HandleAddItem(Item);
}
