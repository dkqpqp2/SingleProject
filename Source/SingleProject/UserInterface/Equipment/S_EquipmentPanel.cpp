// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EquipmentPanel.h"
#include "UserInterface/Equipment/S_EquipmentSlot.h"
#include "Character/S_CharacterPlayer.h"
#include "Components/S_EquipmentComponent.h"
#include "UserInterface/Inventory/S_ItemDragDropOperation.h"
#include "Components/S_InventoryComponent.h"

#include "Components/TextBlock.h"
#include "Items/S_ItemBase.h"

void US_EquipmentPanel::NativeConstruct()
{
    Super::NativeConstruct();

    // 슬롯 초기화
    InitializeSlots();

    SlotWidgetMap = {
        {ESlotName::Weapon, WeaponSlot},
        {ESlotName::Helmet, HelmetSlot},
        {ESlotName::Armor, ArmorSlot},
        {ESlotName::Shield, ShieldSlot},
        {ESlotName::Boots, BootsSlot}
    };

    // 각 슬롯에 SlotName을 설정해줌
    WeaponSlot->SetSlotName(ESlotName::Weapon);
    HelmetSlot->SetSlotName(ESlotName::Helmet);
    ArmorSlot->SetSlotName(ESlotName::Armor);
    ShieldSlot->SetSlotName(ESlotName::Shield);
    BootsSlot->SetSlotName(ESlotName::Boots);
}

void US_EquipmentPanel::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    PlayerCharacter = Cast<AS_CharacterPlayer>(GetOwningPlayerPawn());
    if (PlayerCharacter)
    {
        OwningEquipment = PlayerCharacter->GetEquipment();
        if (OwningEquipment)
        {
            OwningEquipment->OnEquipmentUpdated.AddUObject(this, &US_EquipmentPanel::RefreshEquipmentSlot);
            SetInfoText();
        }
    }

}

bool US_EquipmentPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    const US_ItemDragDropOperation* ItemDragDrop = Cast<US_ItemDragDropOperation>(InOperation);

    if (ItemDragDrop && ItemDragDrop->SourceItem)
    {
        ItemDragDrop->SourceItem->Use(PlayerCharacter, ItemDragDrop->SourceItem);
        return true;
    }
    return false;
}

void US_EquipmentPanel::InitializeSlots()
{
    for (const auto& SlotWidgetPair : SlotWidgetMap)
    {
        TObjectPtr<US_EquipmentSlot> SlotWidget = SlotWidgetPair.Value;
        if (SlotWidget)
        {
            SlotWidget->UpdateSlot();
        }
    }

}

void US_EquipmentPanel::SetInfoText() const
{
    const FString DamageTotalText{ FString::SanitizeFloat(OwningEquipment->GetEquipmentTotalDamage()) };

    const FString ArmorTotalText{ FString::SanitizeFloat(OwningEquipment->GetEquipmentTotalArmor()) };

    DamageInfo->SetText(FText::FromString(DamageTotalText));
    ArmorInfo->SetText(FText::FromString(ArmorTotalText));

}

void US_EquipmentPanel::RefreshEquipmentSlot()
{
    
    if (OwningEquipment)
    {
        for (const auto& SlotWidgetPair : SlotWidgetMap)
        {
            ESlotName SlotName = SlotWidgetPair.Key;
            TObjectPtr<US_EquipmentSlot> SlotWidget = SlotWidgetPair.Value;

            if (SlotWidget)
            {
                US_ItemBase* EquippedItem = OwningEquipment->GetEquippedItem(SlotName);
                if (EquippedItem)
                {
                    SlotWidget->SetItemReference(EquippedItem);
                    SlotWidget->UpdateSlot();
                }
                else
                {
                    SlotWidget->SetItemReference(nullptr);
                    SlotWidget->UpdateSlot();
                }
               
            }
        }
        /*US_ItemBase* Weapon = OwningEquipment->GetEquippedItem(ESlotName::Weapon);
        if (Weapon)
        {
            WeaponSlot->SetItemReference(Weapon);
            WeaponSlot->UpdateSlot();
        }
        else
        {
            WeaponSlot->SetItemReference(nullptr);
            WeaponSlot->UpdateSlot();
        }*/
    }
    SetInfoText();
}