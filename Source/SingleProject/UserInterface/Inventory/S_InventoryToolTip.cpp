// Fill out your copyright notice in the Description page of Project Settings.


#include "S_InventoryToolTip.h"
#include "Items/S_ItemBase.h"
#include "UserInterface/Inventory/S_InventoryItemSlot.h"
#include "Components/TextBlock.h"

void US_InventoryToolTip::NativeConstruct()
{
	Super::NativeConstruct();

	US_ItemBase* ItemBeingHovered = InventorySlotBeingHovered->GetItemReference();

	switch (ItemBeingHovered->ItemType)
	{
	case EItemType::Armor:
		ItemType->SetText(FText::FromString(TEXT("방어구")));
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		ArmorRating->SetVisibility(ESlateVisibility::Visible);
		break;
	case EItemType::Weapon:
		ItemType->SetText(FText::FromString(TEXT("무기")));
		DamageValue->SetVisibility(ESlateVisibility::Visible);
		ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EItemType::Helmet:
		ItemType->SetText(FText::FromString(TEXT("투구")));
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		ArmorRating->SetVisibility(ESlateVisibility::Visible);
		break;
	case EItemType::Shield:
		break;
	case EItemType::Spell:
		ItemType->SetText(FText::FromString(TEXT("마법 아이템")));
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
		break; 
	case EItemType::Boots:
		break;
	case EItemType::Consumable:
		ItemType->SetText(FText::FromString(TEXT("소모 아이템")));
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EItemType::Quest:
		ItemType->SetText(FText::FromString(TEXT("퀘스트 아이템")));
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
		UsageText->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EItemType::Mundane:
		ItemType->SetText(FText::FromString(TEXT("일반 아이템")));
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
		UsageText->SetVisibility(ESlateVisibility::Collapsed);
		ItemName->SetVisibility(ESlateVisibility::Visible);
		UsageText->SetVisibility(ESlateVisibility::Visible);
		ItemDescription->SetVisibility(ESlateVisibility::Visible);
		break;
	default:;
	}
	// 나중에 수정 데미지 방어력 0.0 으로 나옴 아이템 이름도 안나옴
	const FString ItemNameInfo = ItemBeingHovered->ItemTextData.Name.ToString();
	ItemName->SetText((FText::FromString(ItemNameInfo)));
	UsageText->SetText((FText::FromString(ItemBeingHovered->ItemTextData.UsageText.ToString())));
	ItemDescription->SetText((FText::FromString(ItemBeingHovered->ItemTextData.Description.ToString())));

	
	const FString ArmorInfo = { TEXT("Armor: ") + FString::SanitizeFloat(ItemBeingHovered->ItemStatistics.ArmorRating) };
	ArmorRating->SetText(FText::FromString(ArmorInfo));

	const FString DamageInfo = { TEXT("Damage: ") + FString::SanitizeFloat(ItemBeingHovered->ItemStatistics.DamageValue) };
	DamageValue->SetText(FText::FromString(DamageInfo));

	const FString WeightInfo = { TEXT("무게: ") + FString::SanitizeFloat(ItemBeingHovered->GetItemStackWeight()) };

	StackWeight->SetText(FText::FromString(WeightInfo));

	if (ItemBeingHovered->ItemNumericData.bIsStackable)
	{
		const FString StackInfo = { TEXT("최대 개수: ") + FString::FromInt(ItemBeingHovered->ItemNumericData.MaxStackSize) };
		MaxStackSize->SetText(FText::FromString(StackInfo));
	}
	else
	{
		MaxStackSize->SetVisibility(ESlateVisibility::Collapsed);
	}
}
