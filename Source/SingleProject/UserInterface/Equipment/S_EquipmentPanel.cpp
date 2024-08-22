// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EquipmentPanel.h"
#include "UserInterface/Equipment/S_EquipmentSlot.h"
#include "Character/S_CharacterPlayer.h"
#include "Components/S_EquipmentComponent.h"
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
    /*if (WeaponSlot)
    {
        WeaponSlot->UpdateSlot();
    }
    if (HelmetSlot)
    {
        HelmetSlot->UpdateSlot();
    }
    if (ArmorSlot)
    {
        ArmorSlot->UpdateSlot();
    }
    if (ShieldSlot)
    {
        ShieldSlot->UpdateSlot();
    }
    if (BootsSlot)
    {
        BootsSlot->UpdateSlot();
    }*/
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