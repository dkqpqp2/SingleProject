// Fill out your copyright notice in the Description page of Project Settings.


#include "S_NewCraftPanel.h"

#include "S_NewCraftDetailInfo.h"
#include "S_NewCraftItemEntry.h"
#include "S_GameInstance.h"
#include "Components/TreeView.h"
#include "Data/ItemDataStructs.h"
#include "Kismet/GameplayStatics.h"

// UWIdget -> US_NewCraftPanel::NativeOnInitialized()
//
// UWIdget::Initialize()
// 	US_NewCraftPanel->NativeOnInitialized()
// 		a
// 		b
// 		c
// 		d
// ---->
// UWIdget::Initialize()
// 	BeginPlay
//
// UWIdget::Initialize()
// {
// 	US_NewCraftPanel->NativeOnInitialized()
// 	{
// 		a
// 		b
// 		c
// 		d
// 	}
// ---->
// 	BeginPlay()
// }
//
// code
// [
// 0x40000
// ~
// 0x30000
// ]
// data
// [
// 0x20000
// ~
// 0x10000
// ]
// heap
// [
// new
// 0x9999
//
//
// 0x5000
// ]
//
// stack
// [
// 0x4999	
// d
// c
// b
// a
// 0x0000
// ]

void US_NewCraftPanel::NativeOnInitialized()
{
	US_GameInstance* GameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance == nullptr)
	{
		return;
	}

	TArray<FName> AllCraftIDList = GameInstance->GetAllDataID<FCraftItemData>();
	if (AllCraftIDList.Num() == 0)
	{
		return;
	}

	//전체 제작 아이템을 순회하면서
	//아이템 타입 별로 Root 위젯을 구성하고, 그 하위에 조합 아이템을 표기하기
	TMap<EItemType, US_NewCraftTreeItemEntry*> CraftCategoryMap;
	for (const auto& ID : AllCraftIDList)
	{
		const FCraftItemData* Data = GameInstance->GetData<FCraftItemData>(ID);
		if (Data == nullptr)
		{
			continue;
		}

		US_NewCraftTreeItemEntry*& RootItem = CraftCategoryMap.FindOrAdd(Data->ResultItemData.ItemType);
		if (RootItem == nullptr)
		{
			RootItem = NewObject<US_NewCraftTreeItemEntry>();;
			RootItem->CraftItemData = Data;
			RootItem->TreeDepth = 0;
		}

		US_NewCraftTreeItemEntry* CraftItem = NewObject<US_NewCraftTreeItemEntry>();
		CraftItem->RootItem = RootItem;
		CraftItem->CraftItemData = Data;
		CraftItem->TreeDepth = RootItem->TreeDepth + 1;
		RootItem->AddChild(CraftItem);
	}

	for (const auto& CraftRootItem : CraftCategoryMap)
	{
		CraftItemList.Add(CraftRootItem.Value);
	}

	CraftItemView->SetListItems(CraftItemList);
	CraftItemView->CollapseAll();
	CraftItemView->OnItemClicked().AddUObject(this, &ThisClass::OnCraftItemClicked);
	CraftItemView->OnItemExpansionChanged().AddUObject(this, &ThisClass::OnCraftItemExpansionChanged);
	CraftItemView->SetOnGetItemChildren(this, &ThisClass::OnCraftItemGetChildren);
	CraftDetailInfo->SetVisibility(ESlateVisibility::Collapsed);
}

void US_NewCraftPanel::OnCraftItemClicked(UObject* InItem)
{
	US_NewCraftTreeItemEntry* CraftItem = Cast<US_NewCraftTreeItemEntry>(InItem);
	if (CraftItem == nullptr)
	{
		return;
	}
	if (CraftItem->CraftItemData == nullptr)
	{
		return;
	}
	if (CraftItem->RootItem == nullptr)
	{
		CraftDetailInfo->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	CraftDetailInfo->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	CraftDetailInfo->SetCraftItemData(*CraftItem->CraftItemData);
}

void US_NewCraftPanel::OnCraftItemExpansionChanged(UObject* InItem, bool InIsExpanded)
{
	US_NewCraftTreeItemEntry* CraftItem = Cast<US_NewCraftTreeItemEntry>(InItem);
	if (CraftItem == nullptr)
	{
		return;
	}
}

void US_NewCraftPanel::OnCraftItemGetChildren(UObject* InItem, TArray<UObject*>& Children)
{
	US_NewCraftTreeItemEntry* CraftItem = Cast<US_NewCraftTreeItemEntry>(InItem);
	if (CraftItem == nullptr)
	{
		return;
	}

	if (CraftItem->HasChildren())
	{
		for (auto& Child : CraftItem->GetAllChildren())
		{
			Children.Add(Child);
		}
	}
}
