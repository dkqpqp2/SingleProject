// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_InventoryItemSlot.generated.h"

class US_ItemBase;
class AS_CharacterPlayer;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_InventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItemReference(US_ItemBase* ItemIn) { ItemReference = ItemIn; };
	TObjectPtr<US_ItemBase> GetItemReference() const { return ItemReference; };

	void OnItemClicked();

protected:
	UPROPERTY()
	AS_CharacterPlayer* OwningPlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
	TSubclassOf<class US_DragItemVisual> DragItemVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
	TSubclassOf<class US_InventoryToolTip> ToolTipClass;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot")
	TObjectPtr<class US_ItemBase> ItemReference;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
	TObjectPtr<class UBorder> ItemBorder;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
	TObjectPtr<class UImage>ItemIcon;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemQuantity;

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
