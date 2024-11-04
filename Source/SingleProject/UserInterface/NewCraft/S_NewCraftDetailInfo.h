// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/NewCraft/S_NewCraftInfo.h"
#include "S_NewCraftDetailInfo.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_NewCraftDetailInfo : public US_NewCraftInfo
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void SetCraftItemData(const FCraftItemData& InCraftItemData) override;

protected:
	UFUNCTION()
	void OnClickedCraft();

	void OnInventroyUpdated();

	/*UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Img_ResultItem;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Label_ResultName;*/
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Label_Description;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_Craft;

	UPROPERTY()
	TObjectPtr<class US_NewCraftComponent> OwningCraft;
	UPROPERTY()
	TObjectPtr<class US_InventoryComponent> OwningInventory;

	UPROPERTY()
	FName CraftID;
};
