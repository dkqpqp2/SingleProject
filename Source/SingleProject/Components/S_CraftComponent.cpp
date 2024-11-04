// Fill out your copyright notice in the Description page of Project Settings.

#include "S_CraftComponent.h"

#include "S_GameInstance.h"
#include "S_InventoryComponent.h"
#include "Data/ItemDataStructs.h"
#include "Items/S_ItemBase.h"
#include "Kismet/KismetSystemLibrary.h"

US_CraftComponent::US_CraftComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void US_CraftComponent::CraftItem(const FName& InCraftItemID)
{
	UKismetSystemLibrary::PrintString(this, TEXT("제작중 뚝딱뚝닥"));

	const FCraftItemData* CraftItemData = US_GameInstance::GetData<FCraftItemData>(this, InCraftItemID);
	if(CraftItemData == nullptr)
	{
		return;
	}

	const FItemData* ResultItem = US_GameInstance::GetData<FItemData>(this, CraftItemData->ResultItemData.ID);
	if(ResultItem == nullptr)
	{
		return;
	}

	US_ItemBase* NewItem = US_ItemBase::CreateItem(this, *ResultItem);
	if(NewItem == nullptr)
	{
		return;
	}

	InventoryReference->HandleAddItem(NewItem);
}

bool US_CraftComponent::IsCraftable(const FName& InCraftItemID)
{
	return true;
}

void US_CraftComponent::BeginPlay()
{
	Super::BeginPlay();

	InventoryReference = GetOwner()->FindComponentByClass<US_InventoryComponent>();
}
