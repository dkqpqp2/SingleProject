// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S_CraftInfo.h"
#include "Blueprint/UserWidget.h"
#include "S_CraftDetailInfo.generated.h"

class US_InventoryComponent;
class US_CraftComponent;
class UButton;
/**
 *
 */
UCLASS()
class SINGLEPROJECT_API US_CraftDetailInfo : public US_CraftInfo
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void SetCraftItemData(const FCraftItemData& InCraftItemData) override;

protected:
	UFUNCTION()
	void OnClickedCraft();

	void OnInventoryUpdated();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Label_Description;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_Craft;

	UPROPERTY()
	TObjectPtr<US_CraftComponent> OwningCraft;
	UPROPERTY()
	TObjectPtr<US_InventoryComponent> OwningInventory;

	UPROPERTY()
	FName CraftID;
};
