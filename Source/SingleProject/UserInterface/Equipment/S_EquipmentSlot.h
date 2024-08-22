// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/S_ItemBase.h"
#include "Components/S_EquipmentComponent.h"
#include "S_EquipmentSlot.generated.h"

class US_ItemBase;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_EquipmentSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetItemReference(US_ItemBase* ItemIn) { EquippedItem = ItemIn; };
	TObjectPtr<US_ItemBase> GetItemReference() const { return EquippedItem; };

	void UpdateSlot();

	void OnItemClicked();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TObjectPtr<class US_ItemBase> EquippedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TObjectPtr<class US_InventoryItemSlot> ItemReference;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
	TObjectPtr<class UBorder> ItemBorder;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<class UTexture2D> EmptyTexture;

	TMap<ESlotName, FName> SlotToSocketMap;

	bool bIsEmpty;

	ESlotName SlotWidgetName;

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
