// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_InventoryToolTip.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_InventoryToolTip : public UUserWidget
{
	GENERATED_BODY()

public:
	TObjectPtr<class US_InventoryItemSlot> InventorySlotBeingHovered;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemType;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> DamageValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ArmorRating;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> UsageText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemDescription;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> MaxStackSize;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> StackWeight;

protected:
	virtual void NativeConstruct() override;
	
};
