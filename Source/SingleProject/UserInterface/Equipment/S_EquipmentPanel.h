// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_EquipmentPanel.generated.h"

class US_EquipmentSlot;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_EquipmentPanel : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<US_EquipmentSlot> WeaponSlot;

	UPROPERTY(meta = (BindWidget))        
	TObjectPtr<US_EquipmentSlot> HelmetSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<US_EquipmentSlot> ArmorSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<US_EquipmentSlot> ShieldSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<US_EquipmentSlot> BootsSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> DamageInfo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ArmorInfo;

	UPROPERTY()
	TObjectPtr<class AS_CharacterPlayer> PlayerCharacter;

	UPROPERTY()
	TObjectPtr<class US_EquipmentComponent> OwningEquipment;

	UPROPERTY()
	TSubclassOf<class US_EquipmentSlot> EquipmentSlotClass;

	UFUNCTION()
	void RefreshEquipmentSlot();

	TMap<ESlotName, TObjectPtr<US_EquipmentSlot>> SlotWidgetMap;


protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

	void InitializeSlots();

	void SetInfoText()const;
};
