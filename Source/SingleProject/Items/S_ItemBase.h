// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStructs.h"
#include "S_ItemBase.generated.h"

class AS_CharacterPlayer;
class US_InventoryComponent;
class US_EquipmentSlot;


UENUM()
enum class ESlotName : uint8
{
	Weapon UMETA(DisplayName = "무기"),
	Helmet UMETA(DisplayName = "투구"),
	Armor UMETA(DisplayName = "방어구"),
	Shield UMETA(DisplayName = "방패"),
	Boots UMETA(DisplayName = "신발")
};
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_ItemBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<US_InventoryComponent> OwningInventory;

	UPROPERTY()
	TObjectPtr<class US_EquipmentComponent> OwningEquipment;

	UPROPERTY()
	TObjectPtr<class US_EquipmentSlot> EquipmentSlot;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 Quantity;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName ID;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemTextData ItemTextData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemNumericData ItemNumericData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemAssetData ItemAssetData;

	bool bIsCopy;
	bool bIsPickup;

	US_ItemBase();

	void ResetItemFlags();

	TObjectPtr<US_ItemBase> CreateItemCopy() const;
	TObjectPtr<US_ItemBase> CreateItem(const AS_CharacterPlayer* Player);

	void SetOwner(AS_CharacterPlayer* Character);

	UFUNCTION(Category = "Item")
	float GetItemStackWeight() const { return Quantity * ItemNumericData.Weight; };

	UFUNCTION(Category = "Item")
	float GetItemSingleWeight() const { return ItemNumericData.Weight; };

	UFUNCTION(Category = "Item")
	bool IsFullItemStack() const { return Quantity == ItemNumericData.MaxStackSize; };

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category = "Item")
	virtual void Use(AS_CharacterPlayer* Character, US_ItemBase* UseItem);

	void EquipToSocket(AS_CharacterPlayer* Character, const FName& SocketName);

protected:
	bool operator==(const FName& OtherID) const
	{
		return ID == OtherID;
	}

	UPROPERTY()
	TObjectPtr<AS_CharacterPlayer> OwnerCharacter;
};
