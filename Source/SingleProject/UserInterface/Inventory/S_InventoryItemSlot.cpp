// Fill out your copyright notice in the Description page of Project Settings.


#include "S_InventoryItemSlot.h"
#include "UserInterface/Inventory/S_InventoryToolTip.h"
#include "Items/S_ItemBase.h"
#include "UserInterface/Inventory/S_DragItemVisual.h"
#include "UserInterface/Inventory/S_ItemDragDropOperation.h"
#include "Character/S_CharacterPlayer.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void US_InventoryItemSlot::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (ToolTipClass)
    {
        US_InventoryToolTip* ToolTip = CreateWidget<US_InventoryToolTip>(this, ToolTipClass);
        ToolTip->InventorySlotBeingHovered = this;
        SetToolTip(ToolTip);
    }
}

void US_InventoryItemSlot::NativeConstruct()
{
    Super::NativeConstruct();
	if (ItemReference)
	{
		switch (ItemReference->ItemQuality)
		{
		case EItemQuality::Shoddy:
			ItemBorder->SetBrushColor(FLinearColor::Gray);
			break;
		case EItemQuality::Common:
			ItemBorder->SetBrushColor(FLinearColor(0.0f, 0.51f, 0.169f));
			break;
		case EItemQuality::Masterwork:
			ItemBorder->SetBrushColor(FLinearColor(0.0f, 0.4f, 0.75f));
			break;
		case EItemQuality::GrandMaster:
			ItemBorder->SetBrushColor(FLinearColor(1.0f, 0.45f, 0.0f)); // Orange
			break;
		default:;
		}
		
		ItemIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);

		if (ItemReference->ItemNumericData.bIsStackable)
		{
			ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));
		}
		else
		{
			ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

FReply US_InventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		OnItemClicked();
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::RightMouseButton);
	}
	return Reply.Unhandled();
}

void US_InventoryItemSlot::OnItemClicked()
{
	OwningPlayerCharacter = Cast<AS_CharacterPlayer>(GetOwningPlayerPawn());
	//OwningPlayerCharacter = Cast<AS_CharacterPlayer>(GetOwningLocalPlayer());
	if (OwningPlayerCharacter && ItemReference)
	{
		ItemReference->Use(OwningPlayerCharacter, ItemReference);
	
	}
}

void US_InventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void US_InventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (DragItemVisualClass)
	{
		const TObjectPtr<US_DragItemVisual> DragVisual = CreateWidget<US_DragItemVisual>(this, DragItemVisualClass);
		DragVisual->ItemIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
		DragVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());

		ItemReference->ItemNumericData.bIsStackable
			? DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity))
			: DragVisual->ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);

		US_ItemDragDropOperation* DragItemOperation = NewObject<US_ItemDragDropOperation>();
		DragItemOperation->SourceItem = ItemReference;
		DragItemOperation->SourceInventory = ItemReference->OwningInventory;

		DragItemOperation->DefaultDragVisual = DragVisual;
		DragItemOperation->Pivot = EDragPivot::TopLeft;

		OutOperation = DragItemOperation;

	}
}

bool US_InventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
