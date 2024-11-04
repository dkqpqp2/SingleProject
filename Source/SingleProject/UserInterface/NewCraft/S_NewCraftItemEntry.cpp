// Fill out your copyright notice in the Description page of Project Settings.


#include "S_NewCraftItemEntry.h"

#include "S_NewCraftInfo.h"
#include "S_GameInstance.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Data/ItemDataStructs.h"
#include "S_NewCraftMaterialItem.h"


bool US_NewTreeItemEntry::HasChildren() const
{
	return TreeChildren.Num() > 0;
}

TArray<class US_NewTreeItemEntry*> US_NewTreeItemEntry::GetAllChildren() const
{
	return TreeChildren;
}

void US_NewTreeItemEntry::AddChild(US_NewTreeItemEntry* InChild)
{
	TreeChildren.AddUnique(InChild);
}

void US_NewTreeItemEntry::RemoveChild(US_NewTreeItemEntry* InChild)
{
	TreeChildren.Remove(InChild);
}

void US_NewTreeItemEntry::ClearChildren()
{
	TreeChildren.Reset();
}

void US_NewCraftItemEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	US_NewCraftTreeItemEntry* ItemEntry = Cast<US_NewCraftTreeItemEntry>(ListItemObject);
	if (ItemEntry == nullptr)
	{
		return;
	}
	if (ItemEntry->CraftItemData == nullptr)
	{
		return;
	}

	SwitcherTreeItem->SetActiveWidgetIndex(ItemEntry->TreeDepth);
	if (ItemEntry->HasChildren())
	{
		UpdateCategory(*ItemEntry->CraftItemData);
	}
	else
	{
		UpdateMaterials(*ItemEntry->CraftItemData);
	}
}

void US_NewCraftItemEntry::NativeConstruct()
{
	Super::NativeConstruct();
	Img_Selection->SetVisibility(ESlateVisibility::Collapsed);
}

void US_NewCraftItemEntry::NativeDestruct()
{
	Super::NativeDestruct();
}

void US_NewCraftItemEntry::NativeOnItemExpansionChanged(bool bIsExpanded)
{
	IUserObjectListEntry::NativeOnItemExpansionChanged(bIsExpanded);

	if (bIsExpanded)
	{
		SwitcherArrow->SetActiveWidget(Img_Expanded);
	}
	else
	{
		SwitcherArrow->SetActiveWidget(Img_Collapsed);
	}
}

void US_NewCraftItemEntry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);

	US_NewCraftTreeItemEntry* Item = GetListItem<US_NewCraftTreeItemEntry>();
	if (Item == nullptr)
	{
		return;
	}

	if (bIsSelected)
	{
		Img_Selection->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		Img_Selection->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void US_NewCraftItemEntry::UpdateCategory(const FCraftItemData& InCraftItemData)
{
	FText Name = UEnum::GetDisplayValueAsText(InCraftItemData.ResultItemData.ItemType);
	Label_CategoryName->SetText(Name);
}

void US_NewCraftItemEntry::UpdateMaterials(const FCraftItemData& InCraftItemData)
{
	CraftInfo->SetCraftItemData(InCraftItemData);
}
