// Fill out your copyright notice in the Description page of Project Settings.

#include "S_CraftDetailInfo.h"

#include "Components/Button.h"
#include "Components/S_CraftComponent.h"
#include "Components/S_InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Data/ItemDataStructs.h"
#include "Kismet/KismetSystemLibrary.h"

void US_CraftDetailInfo::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Craft->OnClicked.AddDynamic(this, &ThisClass::OnClickedCraft);

	OwningCraft = GetOwningPlayerPawn()->FindComponentByClass<US_CraftComponent>();
	OwningInventory = GetOwningPlayerPawn()->FindComponentByClass<US_InventoryComponent>();
	if(OwningInventory != nullptr)
	{
		OwningInventory->OnInventoryUpdated.AddUObject(this, &ThisClass::OnInventoryUpdated);
	}
}

void US_CraftDetailInfo::NativeDestruct()
{
	Super::NativeDestruct();

	Btn_Craft->OnClicked.RemoveAll(this);

	if(OwningInventory != nullptr)
	{
		OwningInventory->OnInventoryUpdated.RemoveAll(this);
	}
	OwningInventory = nullptr;
	OwningCraft = nullptr;
}

void US_CraftDetailInfo::SetCraftItemData(const FCraftItemData& InCraftItemData)
{
	Super::SetCraftItemData(InCraftItemData);

	CraftID = InCraftItemData.ID;

	Label_Description->SetText(InCraftItemData.CraftDescription);
}

void US_CraftDetailInfo::OnClickedCraft()
{
	UKismetSystemLibrary::PrintString(this, TEXT("제작 버튼 클릭"));

	OwningCraft->CraftItem(CraftID);
}

void US_CraftDetailInfo::OnInventoryUpdated()
{
	UKismetSystemLibrary::PrintString(this, TEXT("인벤토리 업데이트"));
}
