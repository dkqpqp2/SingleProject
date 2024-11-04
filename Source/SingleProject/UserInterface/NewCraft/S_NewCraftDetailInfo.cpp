// Fill out your copyright notice in the Description page of Project Settings.


#include "S_NewCraftDetailInfo.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/S_NewCraftComponent.h"
#include "Components/S_InventoryComponent.h"
#include "Data/ItemDataStructs.h"
#include "Kismet/KismetSystemLibrary.h"

void US_NewCraftDetailInfo::NativeConstruct()
{
	Super::NativeConstruct();
	
	Btn_Craft->OnClicked.AddDynamic(this, &ThisClass::OnClickedCraft);

	OwningCraft = GetOwningPlayerPawn()->FindComponentByClass<US_NewCraftComponent>();
	OwningInventory = GetOwningPlayerPawn()->FindComponentByClass<US_InventoryComponent>();
	if (OwningInventory != nullptr)
	{
		OwningInventory->OnInventoryUpdated.AddUObject(this, &ThisClass::OnInventroyUpdated);
	}

}

void US_NewCraftDetailInfo::NativeDestruct()
{
	Super::NativeDestruct();

	Btn_Craft->OnClicked.RemoveAll(this);

	if (OwningInventory != nullptr)
	{
		OwningInventory->OnInventoryUpdated.RemoveAll(this);
	}
	OwningInventory = nullptr;
	OwningCraft = nullptr;
}

void US_NewCraftDetailInfo::SetCraftItemData(const FCraftItemData& InCraftItemData)
{
	Super::SetCraftItemData(InCraftItemData);

	CraftID = InCraftItemData.ID;
	
	Label_Description->SetText(InCraftItemData.CraftDescription);
}

void US_NewCraftDetailInfo::OnClickedCraft()
{
	UKismetSystemLibrary::PrintString(this, TEXT("제작 버튼 클릭"));

	OwningCraft->CraftItem(CraftID);
}

void US_NewCraftDetailInfo::OnInventroyUpdated()
{
	UKismetSystemLibrary::PrintString(this, TEXT("인벤토리 업데이트"));
}
