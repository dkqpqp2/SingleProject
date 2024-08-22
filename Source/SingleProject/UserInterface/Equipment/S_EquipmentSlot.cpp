// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EquipmentSlot.h"
#include "GameFramework/Character.h"
#include "Items/S_ItemBase.h"
#include "UserInterface/Inventory/S_ItemDragDropOperation.h"
#include "UserInterface/Inventory/S_InventoryItemSlot.h"

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
	//OwningPlayerCharacter = Cast<AS_CharacterPlayer>(GetOwningLocalPlayer());
	if (OwningPlayerCharacter && EquippedItem)
	{
		US_InventoryComponent* InventoryComponent = OwningPlayerCharacter->FindComponentByClass<US_InventoryComponent>();
		if (InventoryComponent)
		{
			InventoryComponent->HandleAddItem(EquippedItem);

			EquippedItem = nullptr;
		}

		US_EquipmentComponent* EquipmentComponent = OwningPlayerCharacter->FindComponentByClass<US_EquipmentComponent>();
		if (EquipmentComponent)
		{			
			ESlotName SlotName = EquipmentComponent->GetSlotNames();

			if (SlotToSocketMap.Contains(SlotName))
			{
				FName SocketName = SlotToSocketMap[SlotName];
				EquipmentComponent->UnequipItem(SlotName, SocketName);

				//EquipmentComponent->UnequipItem(ESlotName::Weapon, TEXT("WeaponSocket"));
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

