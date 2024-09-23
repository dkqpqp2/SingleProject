// Fill out your copyright notice in the Description page of Project Settings.


#include "S_InventoryToolTip.h"
#include "Items/S_ItemBase.h"
#include "UserInterface/Inventory/S_InventoryItemSlot.h"
#include "Components/TextBlock.h"

void US_InventoryToolTip::NativeConstruct()
{
	Super::NativeConstruct();

	US_ItemBase* ItemBeingHovered = InventorySlotBeingHovered->GetItemReference();

	if (!ItemBeingHovered)
	{
		return;
	}

	UpdateItemType(ItemBeingHovered);
	UpdateItemText(ItemBeingHovered);
	UpdateItemStats(ItemBeingHovered);
}

void US_InventoryToolTip::UpdateItemType(US_ItemBase* Item)
{
	switch (Item->ItemType)
	{
	case EItemType::Armor:
		SetItemTypeText(TEXT("방어구"), true);
		break;
	case EItemType::Weapon:
		SetItemTypeText(TEXT("무기"), false);
		break;
	case EItemType::Helmet:
		SetItemTypeText(TEXT("투구"), true);
		break;
	case EItemType::Shield:
		SetItemTypeText(TEXT("방패"), true);
		break;
	case EItemType::Spell:
		SetIngredientItemTypeText(TEXT("마법 아이템"));
		break;
	case EItemType::Consumable:
		SetIngredientItemTypeText(TEXT("소모 아이템"));
		break;
	case EItemType::Quest:
		SetIngredientItemTypeText(TEXT("퀘스트 아이템"));
		UsageText->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EItemType::Mundane:
		SetIngredientItemTypeText(TEXT("일반 아이템"));
		break;
	default:
		break;
	}
}

void US_InventoryToolTip::SetItemTypeText(const FString& TypeText, bool bShowDamageOrArmorRating)
{
	ItemType->SetText(FText::FromString(TypeText));
	DamageValue->SetVisibility(bShowDamageOrArmorRating ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
	ArmorRating->SetVisibility(bShowDamageOrArmorRating ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void US_InventoryToolTip::SetIngredientItemTypeText(const FString& TypeText)
{
	ItemType->SetText(FText::FromString(TypeText));
	DamageValue->SetVisibility(ESlateVisibility::Collapsed);
	ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
}

void US_InventoryToolTip::UpdateItemText(US_ItemBase* Item)
{
	ItemName->SetText(FText::FromString(Item->ItemTextData.Name.ToString()));
	UsageText->SetText(FText::FromString(Item->ItemTextData.UsageText.ToString()));
	ItemDescription->SetText(FText::FromString(Item->ItemTextData.Description.ToString()));
}

void US_InventoryToolTip::UpdateItemStats(US_ItemBase* Item)
{
	ArmorRating->SetText(FText::FromString(FString::Printf(TEXT("방어력: %.2f"), Item->ItemStatistics.ArmorRating)));
	DamageValue->SetText(FText::FromString(FString::Printf(TEXT("공격력: %.2f"), Item->ItemStatistics.DamageValue)));

	StackWeight->SetText(FText::FromString(FString::Printf(TEXT("무게: %.2f"), Item->GetItemStackWeight())));

	if (Item->ItemNumericData.bIsStackable)
	{
		MaxStackSize->SetText(FText::FromString(FString::Printf(TEXT("최대 개수: %d"), Item->ItemNumericData.MaxStackSize)));
	}
	else
	{
		MaxStackSize->SetVisibility(ESlateVisibility::Collapsed);
	}
}
