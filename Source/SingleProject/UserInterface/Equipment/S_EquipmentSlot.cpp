// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EquipmentSlot.h"
#include "GameFramework/Character.h"
#include "Items/S_ItemBase.h"
#include "UserInterface/Inventory/S_ItemDragDropOperation.h"
#include "UserInterface/Inventory/S_InventoryItemSlot.h"
#include "UserInterface/Inventory/S_DragItemVisual.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/S_EquipmentComponent.h"
#include "Components/S_InventoryComponent.h"

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

	SlotToSocketMap =
	{
		{ESlotName::Weapon, TEXT("WeaponSocket") },
		{ESlotName::Helmet, TEXT("HelmetSocket") },
		{ESlotName::Armor, TEXT("ArmorSocket") },
		{ESlotName::Shield, TEXT("ShieldSocket") },
		{ESlotName::Boots, TEXT("BootsSocket") },
	};

}

FReply US_EquipmentSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		OnItemClicked();
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::RightMouseButton);
	}

	return Reply.Unhandled();
}

void US_EquipmentSlot::OnItemClicked()
{
	ACharacter* OwningPlayerCharacter = Cast<ACharacter>(GetOwningPlayerPawn());
	if (OwningPlayerCharacter && EquippedItem)
	{
		InventoryComponent = OwningPlayerCharacter->FindComponentByClass<US_InventoryComponent>();
		if (InventoryComponent)
		{
			InventoryComponent->HandleAddItem(EquippedItem);

			EquippedItem = nullptr;
		}

		EquipmentComponent = OwningPlayerCharacter->FindComponentByClass<US_EquipmentComponent>();
		if (EquipmentComponent)
		{			
			ESlotName SlotName = GetSlotName();

			if (SlotToSocketMap.Contains(SlotName))
			{
				FName SocketName = SlotToSocketMap[SlotName];
				EquipmentComponent->UnequipItem(SlotName, SocketName);
			}
		}
		
	}
}
void US_EquipmentSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void US_EquipmentSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (EquippedItem == nullptr)
	{
		return;
	}
	if (DragItemVisualClass)
	{
		const TObjectPtr<US_DragItemVisual> DragVisual = CreateWidget<US_DragItemVisual>(this, DragItemVisualClass);

		DragVisual->ItemIcon->SetBrushFromTexture(EquippedItem->ItemAssetData.Icon);
		DragVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());

		EquippedItem->ItemNumericData.bIsStackable
			? DragVisual->ItemQuantity->SetText(FText::AsNumber(EquippedItem->Quantity))
			: DragVisual->ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);

		US_ItemDragDropOperation* DragItemOperation = NewObject<US_ItemDragDropOperation>();

		DragItemOperation->SourceItem = EquippedItem;
		DragItemOperation->EquipmentInventory = EquippedItem->OwningEquipment;

		DragItemOperation->DefaultDragVisual = DragVisual;
		DragItemOperation->Pivot = EDragPivot::TopLeft;

		OutOperation = DragItemOperation;
	}
}

bool US_EquipmentSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	const US_ItemDragDropOperation* ItemDragDropOperation = Cast<US_ItemDragDropOperation>(InOperation);

	if (ItemDragDropOperation && ItemDragDropOperation->SourceItem)
	{
		EquipItemToSlot(ItemDragDropOperation->SourceItem);
		/*switch (ItemDragDropOperation->SourceItem->ItemType)
		{
		case EItemType::Weapon:
			ItemDragDropOperation->SourceItem->OwningEquipment->EquipItem(ESlotName::Weapon, TEXT("WeaponSocket"), ItemDragDropOperation->SourceItem);
			ItemDragDropOperation->SourceItem->OwningInventory->RemoveAmountOfItem(ItemDragDropOperation->SourceItem, ItemDragDropOperation->SourceItem->Quantity);
			break;
		case EItemType::Armor:
			ItemDragDropOperation->SourceItem->OwningEquipment->EquipItem(ESlotName::Armor, TEXT("ArmorSocket"), ItemDragDropOperation->SourceItem);
			ItemDragDropOperation->SourceItem->OwningInventory->RemoveAmountOfItem(ItemDragDropOperation->SourceItem, ItemDragDropOperation->SourceItem->Quantity);
			break;
		case EItemType::Helmet:
			ItemDragDropOperation->SourceItem->OwningEquipment->EquipItem(ESlotName::Helmet, TEXT("HelmetSocket"), ItemDragDropOperation->SourceItem);
			ItemDragDropOperation->SourceItem->OwningInventory->RemoveAmountOfItem(ItemDragDropOperation->SourceItem, ItemDragDropOperation->SourceItem->Quantity);
			break;
		case EItemType::Shield:
			ItemDragDropOperation->SourceItem->OwningEquipment->EquipItem(ESlotName::Shield, TEXT("ShieldSocket"), ItemDragDropOperation->SourceItem);
			ItemDragDropOperation->SourceItem->OwningInventory->RemoveAmountOfItem(ItemDragDropOperation->SourceItem, ItemDragDropOperation->SourceItem->Quantity);
			break;
		case EItemType::Boots:
			ItemDragDropOperation->SourceItem->OwningEquipment->EquipItem(ESlotName::Boots, TEXT("BootsSocket"), ItemDragDropOperation->SourceItem);
			ItemDragDropOperation->SourceItem->OwningInventory->RemoveAmountOfItem(ItemDragDropOperation->SourceItem, ItemDragDropOperation->SourceItem->Quantity);
			break;
		default:;
		}*/
		return true;
	}
	return false;
}

void US_EquipmentSlot::EquipItemToSlot(US_ItemBase* Item)
{
	if (!Item)
	{
		return;
	}

	switch (Item->ItemType)
	{
	case EItemType::Weapon:
		Item->OwningEquipment->EquipItem(ESlotName::Weapon, TEXT("WeaponSocket"), Item);
		break;
	case EItemType::Armor:
		Item->OwningEquipment->EquipItem(ESlotName::Armor, TEXT("ArmorSocket"), Item);
		break;
	case EItemType::Helmet:
		Item->OwningEquipment->EquipItem(ESlotName::Helmet, TEXT("HelmetSocket"), Item);
		break;
	case EItemType::Shield:
		Item->OwningEquipment->EquipItem(ESlotName::Shield, TEXT("ShieldSocket"), Item);
		break;
	default:
		break;
	}
	Item->OwningInventory->RemoveAmountOfItem(Item, Item->Quantity);
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

