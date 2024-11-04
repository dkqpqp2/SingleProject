// Fill out your copyright notice in the Description page of Project Settings.

#include "S_CraftPanel.h"

#include "S_CraftDetailInfo.h"
#include "S_CraftItemEntry.h"
#include "S_GameInstance.h"
#include "Components/TreeView.h"
#include "Data/ItemDataStructs.h"
#include "Kismet/GameplayStatics.h"

void US_CraftPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TArray<US_CraftTreeItemEntry*> CraftItemList;
	US_GameInstance* GameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(this));
	if(GameInstance == nullptr)
	{
		return;
	}

	TArray<FName> AllCraftIDList = GameInstance->GetAllDataID<FCraftItemData>();
	if(AllCraftIDList.Num() == 0)
	{
		return;
	}

	//전체 제작 아이템을 순회하면서
	//아이템 타입 별로 Root 위젯을 구성하고, 그 하위에 조합 아이템을 표기하기
	TMap<EItemType, US_CraftTreeItemEntry*> CraftCategoryMap;
	for(const auto& ID : AllCraftIDList)
	{
		const FCraftItemData* Data = GameInstance->GetData<FCraftItemData>(ID);
		if(Data == nullptr)
		{
			continue;
		}

		US_CraftTreeItemEntry*& RootItem = CraftCategoryMap.FindOrAdd(Data->ResultItemData.ItemType);
		if(RootItem == nullptr)
		{
			RootItem = NewObject<US_CraftTreeItemEntry>();;
			RootItem->CraftItemData = Data;
			RootItem->TreeDepth = 0;
		}

		US_CraftTreeItemEntry* CraftItem = NewObject<US_CraftTreeItemEntry>();
		CraftItem->RootItem = RootItem;
		CraftItem->CraftItemData = Data;
		CraftItem->TreeDepth = RootItem->TreeDepth + 1;
		RootItem->AddChild(CraftItem);
	}

	for(const auto& CraftRootItem : CraftCategoryMap)
	{
		CraftItemList.Add(CraftRootItem.Value);
	}

	CraftItemView->SetListItems(CraftItemList);
	CraftItemView->CollapseAll();
	CraftItemView->OnItemClicked().AddUObject(this, &ThisClass::OnCraftItemClicked);
	CraftItemView->OnItemExpansionChanged().AddUObject(this, &ThisClass::OnCraftItemExpansionChanged);
	CraftItemView->SetOnGetItemChildren(this, &ThisClass::OnCraftItemGetChildren);
}

void US_CraftPanel::OnCraftItemClicked(UObject* InItem)
{
	US_CraftTreeItemEntry* CraftItem = Cast<US_CraftTreeItemEntry>(InItem);
	if(CraftItem == nullptr)
	{
		return;
	}
	if(CraftItem->CraftItemData == nullptr)
	{
		return;
	}
	if(CraftItem->RootItem == nullptr)
	{
		CraftDetailInfo->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	CraftDetailInfo->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	CraftDetailInfo->SetCraftItemData(*CraftItem->CraftItemData);
}

void US_CraftPanel::OnCraftItemExpansionChanged(UObject* InItem, bool InIsExpanded)
{
	US_CraftTreeItemEntry* CraftItem = Cast<US_CraftTreeItemEntry>(InItem);
	if(CraftItem == nullptr)
	{
		return;
	}
	
}

void US_CraftPanel::OnCraftItemGetChildren(UObject* InItem, OUT TArray<UObject*>& Children)
{
	US_CraftTreeItemEntry* CraftItem = Cast<US_CraftTreeItemEntry>(InItem);
	if(CraftItem == nullptr)
	{
		return;
	}

	if(CraftItem->HasChildren())
	{
		for(auto& Child : CraftItem->GetAllChildren())
		{
			Children.Add(Child);
		}
	}
}
