// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/S_NewCraftComponent.h"

#include "S_GameInstance.h"
#include "S_InventoryComponent.h"
#include "Data/ItemDataStructs.h"
#include "Items/S_ItemBase.h"
#include "Kismet/KismetSystemLibrary.h"

US_NewCraftComponent::US_NewCraftComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void US_NewCraftComponent::CraftItem(const FName& InCraftItemID)
{
	UKismetSystemLibrary::PrintString(this, TEXT("제작중"));

	const FCraftItemData* CraftItemData = US_GameInstance::GetData<FCraftItemData>(this, InCraftItemID);
	if (CraftItemData == nullptr)
	{
		return;
	}

	if(!InventoryReference->CheckIngredients(CraftItemData->MaterialItemDataList))
	{
		UKismetSystemLibrary::PrintString(this, TEXT("재료 부족"));
		return;
	}
	const FItemData* ResultItem = US_GameInstance::GetData<FItemData>(this, CraftItemData->ResultItemData.ID);
	if (ResultItem == nullptr)
	{
		return;
	}

	US_ItemBase* NewItem = US_ItemBase::CreateItem(this, *ResultItem);
	if (NewItem == nullptr)
	{
		return;
	}

	InventoryReference->HandleAddItem(NewItem);

	for(const FCraftMaterialData& Material : CraftItemData->MaterialItemDataList)
	{
		US_ItemBase* ItemInInventory = InventoryReference->FindItemByID(Material.ID);
		if(ItemInInventory)
		{
			InventoryReference->RemoveAmountOfItem(ItemInInventory, Material.RequiredCount);
		}
	}
	InventoryReference->OnInventoryUpdated.Broadcast();
}

bool US_NewCraftComponent::IsCraftable(const FName& InCraftItemID)
{
	return false;
}


// Called when the game starts
void US_NewCraftComponent::BeginPlay()
{
	Super::BeginPlay();

	InventoryReference = GetOwner()->FindComponentByClass<US_InventoryComponent>();
	
}


