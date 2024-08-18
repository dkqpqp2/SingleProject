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
        EquipmentReference = PlayerCharacter->GetEquipment();
        if (EquipmentReference)
        {
            EquipmentReference->OnEquipmentUpdated.AddUObject(this, &US_EquipmentPanel::RefreshEquipmentSlot);
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
    const FString DamageTotalText{ FString::SanitizeFloat(EquipmentReference->GetEquipmentTotalDamage()) };

    const FString ArmorTotalText{ FString::SanitizeFloat(EquipmentReference->GetEquipmentTotalArmor()) };

    DamageInfo->SetText(FText::FromString(DamageTotalText));
    ArmorInfo->SetText(FText::FromString(ArmorTotalText));

}

void US_EquipmentPanel::RefreshEquipmentSlot()
{
    if (EquipmentReference && EquipmentSlotClass)
    {
        for (auto& Slot : EquipmentReference->GetEquippedItems())
        {
            US_EquipmentSlot* EquipSlot = CreateWidget<US_EquipmentSlot>(this, EquipmentSlotClass);
            EquipSlot->SetItemReference(Slot.Value);
        }
    }
}