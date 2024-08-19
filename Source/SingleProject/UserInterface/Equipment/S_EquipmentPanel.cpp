// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EquipmentPanel.h"
#include "UserInterface/Equipment/S_EquipmentSlot.h"
#include "Character/S_CharacterPlayer.h"
#include "Components/S_EquipmentComponent.h"
#include "Components/TextBlock.h"

void US_EquipmentPanel::NativeConstruct()
{
    Super::NativeConstruct();

    // 슬롯 초기화
    InitializeSlots();
   
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
    if (WeaponSlot)
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
        US_ItemBase* Weapon = OwningEquipment->GetEquippedItem(TEXT("Weapon"));
        if (Weapon)
        {
            WeaponSlot->SetItemReference(Weapon);
            WeaponSlot->UpdateSlot();
        }
        else
        {
            WeaponSlot->SetItemReference(nullptr);
            WeaponSlot->UpdateSlot();
        }
    }
}