// Fill out your copyright notice in the Description page of Project Settings.


#include "S_ItemBase.h"
#include "Data/ItemDataStructs.h"
#include "Components/S_InventoryComponent.h"
#include "UserInterface/Equipment/S_EquipmentSlot.h"
#include "Character/S_CharacterPlayer.h"
#include "Components/S_EquipmentComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UserInterface/Equipment/S_EquipmentPanel.h"


US_ItemBase::US_ItemBase() : bIsCopy(false), bIsPickup(false)
{
}

void US_ItemBase::ResetItemFlags()
{
	bIsCopy = false;
	bIsPickup = false;
}

TObjectPtr<US_ItemBase> US_ItemBase::CreateItemCopy() const
{
	US_ItemBase* ItemCopy = NewObject<US_ItemBase>(StaticClass());

	ItemCopy->ID = this->ID;
	ItemCopy->Quantity = this->Quantity;
	ItemCopy->ItemQuality = this->ItemQuality;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->ItemNumericData = this->ItemNumericData;
	ItemCopy->ItemStatistics = this->ItemStatistics;
	ItemCopy->ItemAssetData = this->ItemAssetData;

	ItemCopy->bIsCopy = true;

	return ItemCopy;
}

void US_ItemBase::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, ItemNumericData.bIsStackable ? ItemNumericData.MaxStackSize : 1);
		if (this->OwningInventory)
		{
			if (this->Quantity <= 0)
			{
				this->OwningInventory->RemoveSingleInstanceOfItem(this);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ItemBase OwningInventory was null (item may be a pickup)"));
		}
	}
}

void US_ItemBase::Use(AS_CharacterPlayer* Character, US_ItemBase* UseItem)
{
	if (!Character)
	{
		return;
	}
	US_ItemBase* EquipItem = this;
	switch (ItemType)
	{
	case EItemType::Weapon:
		EquipToSocket(Character, TEXT("WeaponSocket")); // 무기 소켓에 장착
		OwningInventory->RemoveSingleInstanceOfItem(UseItem);
		Character->EquipmentPanel->RefreshEquipmentSlot();

		break;
	case EItemType::Armor:
		EquipToSocket(Character, TEXT("ArmorSocket")); // 방어구 소켓에 장착
		OwningInventory->RemoveAmountOfItem(UseItem, this->Quantity);

		break;
	case EItemType::Helmet:
		EquipToSocket(Character, TEXT("HelmetSocket")); // 투구 소켓에 장착
		OwningInventory->RemoveAmountOfItem(UseItem, this->Quantity);

		break;
	case EItemType::Shield:
		EquipToSocket(Character, TEXT("ShieldSocket")); // 방패 소켓에 장착
		OwningInventory->RemoveAmountOfItem(UseItem, this->Quantity);

		break;
	case EItemType::Spell:
		break;
	case EItemType::Boots:
		EquipToSocket(Character, TEXT("BootsSocket")); // 신발 소켓에 장착
		OwningInventory->RemoveAmountOfItem(this, this->Quantity);
		EquipmentSlot->SetItemReference(UseItem);
		
		break;
	case EItemType::Consumable:
		OwningInventory->RemoveAmountOfItem(UseItem, 1);
		break;
	case EItemType::Quest:
		break;
	case EItemType::Mundane:
		break;
	}
	
}

void US_ItemBase::EquipToSocket(AS_CharacterPlayer* Character, const FName& SocketName)
{
	if (!Character)
	{
		return;
	}
	USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
	if (CharacterMesh && ItemAssetData.Mesh)
	{
		UStaticMeshComponent* ItemMesh = NewObject<UStaticMeshComponent>(Character);
		ItemMesh->SetStaticMesh(ItemAssetData.Mesh);
		ItemMesh->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
		ItemMesh->RegisterComponent();
	}
}
