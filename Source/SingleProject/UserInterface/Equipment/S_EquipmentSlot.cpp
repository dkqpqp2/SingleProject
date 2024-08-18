// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EquipmentSlot.h"
#include "Items/S_ItemBase.h"
#include "UserInterface/Inventory/S_ItemDragDropOperation.h"
#include "UserInterface/Inventory/S_InventoryItemSlot.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void US_EquipmentSlot::NativeOnInitialized()
{
    Super::NativeOnInitialized();
	UpdateSlot();
}

void US_EquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (EquippedItem)
	{
		switch (EquippedItem->ItemQuality)
		{
		case EItemQuality::Shoddy:
			ItemBorder->SetBrushColor(FLinearColor::Gray);
			break;
		case EItemQuality::Common:
			ItemBorder->SetBrushColor(FLinearColor(0.0f, 0.51f, 0.169f));
			break;
		case EItemQuality::Masterwork:
			ItemBorder->SetBrushColor(FLinearColor(0.0f, 0.4f, 0.75f));
			break;
		case EItemQuality::GrandMaster:
			ItemBorder->SetBrushColor(FLinearColor(1.0f, 0.45f, 0.0f)); // Orange
			break;
		default:;
		}

		ItemIcon->SetBrushFromTexture(EquippedItem->ItemAssetData.Icon);

	}
}

FReply US_EquipmentSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

}

void US_EquipmentSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void US_EquipmentSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
}

bool US_EquipmentSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void US_EquipmentSlot::UpdateSlot()
{
    if (EquippedItem)
    {
        // 아이템이 장착되어 있는 경우
        if (ItemIcon)
        {
            ItemIcon->SetBrushFromTexture(EquippedItem->ItemAssetData.Icon);
			ItemBorder->SetBrushColor(FLinearColor::Green);
			bIsEmpty = false;
        }
    }
    else
    {
        // 슬롯이 비어 있는 경우
        if (ItemIcon)
        {
			ItemIcon->SetBrushFromTexture(EmptyTexture);
			ItemBorder->SetBrushColor(FLinearColor::Red);
			bIsEmpty = true;
        }
    }
}
