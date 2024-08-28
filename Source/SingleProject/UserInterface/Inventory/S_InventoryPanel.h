// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_InventoryPanel.generated.h"

class US_InventoryItemSlot;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_InventoryPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void RefreshInventory();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWrapBox> InventoryWrapBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> WeightInfo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CapacityInfo;

	UPROPERTY()
	TObjectPtr<class AS_CharacterPlayer> PlayerCharacter;

	UPROPERTY()
	TObjectPtr<class US_InventoryComponent> InventoryReference;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<US_InventoryItemSlot> InventorySlotClass;

protected:
	UPROPERTY()
	US_InventoryComponent* InventoryComponent;

	void SetInfoText() const;
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
