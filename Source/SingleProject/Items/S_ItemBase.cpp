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

	ItemCopy->ID = ID;
	ItemCopy->Quantity = Quantity;
	ItemCopy->ItemQuality = ItemQuality;
	ItemCopy->ItemType = ItemType;
	ItemCopy->ItemNumericData = ItemNumericData;
	ItemCopy->ItemStatistics = ItemStatistics;
	ItemCopy->ItemAssetData = ItemAssetData;

	ItemCopy->OwningInventory = OwningInventory;
	ItemCopy->OwningEquipment = OwningEquipment;

	ItemCopy->bIsCopy = true;

	return ItemCopy;
}

TObjectPtr<US_ItemBase> US_ItemBase::CreateItem(const AS_CharacterPlayer* Player)
{
	US_ItemBase* ItemCopy = NewObject<US_ItemBase>(StaticClass());

	ItemCopy->ID = ID;
	ItemCopy->Quantity = Quantity;
	ItemCopy->ItemQuality = ItemQuality;
	ItemCopy->ItemType = ItemType;
	ItemCopy->ItemNumericData = ItemNumericData;
	ItemCopy->ItemStatistics = ItemStatistics;
	ItemCopy->ItemAssetData = ItemAssetData;

	//플레이어가 가지는 인벤토리 및 장비 컴포넌트 세팅
	//ItemCopy->OwningPlayer = Player; 이거로 하면 나중에 다른 컴포넌트 찾아서 사용도 가능
	ItemCopy->OwningInventory = Player->FindComponentByClass<US_InventoryComponent>();
	ItemCopy->OwningEquipment = Player->FindComponentByClass<US_EquipmentComponent>();

	ItemCopy->bIsCopy = true;

	return ItemCopy;
}

void US_ItemBase::SetOwner(AS_CharacterPlayer* Character)
{
	if (!Character)
	{
		return;
	}

	OwnerCharacter = Character;
	OwningInventory = OwnerCharacter->FindComponentByClass<US_InventoryComponent>();
	OwningEquipment = OwnerCharacter->FindComponentByClass<US_EquipmentComponent>();
}

void US_ItemBase::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, ItemNumericData.bIsStackable ? ItemNumericData.MaxStackSize : 1);
		if (OwningInventory)
		{
			if (Quantity <= 0)
			{
				OwningInventory->RemoveSingleInstanceOfItem(this);
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
		OwningEquipment->EquipItem(TEXT("Weapon"), TEXT("WeaponSocket"), this);
		OwningInventory->RemoveAmountOfItem(UseItem, Quantity);

		break;
	case EItemType::Armor:
		EquipToSocket(Character, TEXT("ArmorSocket")); // 방어구 소켓에 장착
		OwningInventory->RemoveAmountOfItem(UseItem, Quantity);

		break;
	case EItemType::Helmet:
		EquipToSocket(Character, TEXT("HelmetSocket")); // 투구 소켓에 장착
		OwningInventory->RemoveAmountOfItem(UseItem, Quantity);

		break;
	case EItemType::Shield:
		EquipToSocket(Character, TEXT("ShieldSocket")); // 방패 소켓에 장착
		OwningInventory->RemoveAmountOfItem(UseItem, Quantity);

		break;
	case EItemType::Spell:
		break;
	case EItemType::Boots:
		EquipToSocket(Character, TEXT("BootsSocket")); // 신발 소켓에 장착
		OwningInventory->RemoveAmountOfItem(UseItem, Quantity);
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
