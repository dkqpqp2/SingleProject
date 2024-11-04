// Fill out your copyright notice in the Description page of Project Settings.

#include "S_CraftItemEntry.h"

#include "S_CraftInfo.h"
#include "S_GameInstance.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Data/ItemDataStructs.h"
#include "S_CraftMaterialItem.h"

bool US_TreeItemEntry::HasChildren() const
{
	return TreeChildren.Num() > 0;
}

TArray<US_TreeItemEntry*> US_TreeItemEntry::GetAllChildren() const
{
	return TreeChildren;
}

void US_TreeItemEntry::AddChild(US_TreeItemEntry* InChild)
{
	TreeChildren.AddUnique(InChild);
}

void US_TreeItemEntry::RemoveChild(US_TreeItemEntry* InChild)
{
	TreeChildren.Remove(InChild);
}

void US_TreeItemEntry::ClearChildren()
{
	TreeChildren.Reset();
}

void US_CraftItemEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	US_CraftTreeItemEntry* ItemEntry = Cast<US_CraftTreeItemEntry>(ListItemObject);
	if(ItemEntry == nullptr)
	{
		return;
	}
	if(ItemEntry->CraftItemData == nullptr)
	{
		return;
	}

	SwitcherTreeItem->SetActiveWidgetIndex(ItemEntry->TreeDepth);
	if(ItemEntry->HasChildren())
	{
		UpdateCategory(*ItemEntry->CraftItemData);
	}
	else
	{
		UpdateMaterials(*ItemEntry->CraftItemData);
	}
}

void US_CraftItemEntry::NativeConstruct()
{
	Super::NativeConstruct();

}

void US_CraftItemEntry::NativeDestruct()
{
	Super::NativeDestruct();

}

void US_CraftItemEntry::NativeOnItemExpansionChanged(bool bIsExpanded)
{
	IUserObjectListEntry::NativeOnItemExpansionChanged(bIsExpanded);

	if(bIsExpanded)
	{
		SwitcherArrow->SetActiveWidget(Img_Expanded);
	}
	else
	{
		SwitcherArrow->SetActiveWidget(Img_Collapsed);
	}
}

void US_CraftItemEntry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);

	US_CraftTreeItemEntry* Item = GetListItem<US_CraftTreeItemEntry>();
	if(Item == nullptr)
	{
		return;
	}

	//선택 이미지가 출력되어야 한다거나 EntryWidget에서 처리되어야 할 것
	if(bIsSelected)
	{
		Img_Selection->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		Img_Selection->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void US_CraftItemEntry::UpdateCategory(const FCraftItemData& InCraftItemData)
{
	FText Name = UEnum::GetDisplayValueAsText(InCraftItemData.ResultItemData.ItemType);
	Label_CategoryName->SetText(Name);
}

void US_CraftItemEntry::UpdateMaterials(const FCraftItemData& InCraftItemData)
{
	CraftInfo->SetCraftItemData(InCraftItemData);
}
