// Fill out your copyright notice in the Description page of Project Settings.


#include "S_QuickSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void US_QuickSlot::SetSkillKeyText(const FString& InKeyText)
{
	if(KeyText)
	{
		KeyText->SetText(FText::FromString(InKeyText));
	}
}

void US_QuickSlot::SetSlotSkillData(const FSkillData& InSkillData)
{
	if(SlotSkillIcon)
	{
		FSlateBrush Brush = SlotSkillIcon->GetBrush();

		Brush.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		Brush.SetResourceObject(InSkillData.SkillAssetData.SkillIcon);
		SlotSkillIcon->SetBrush(Brush);
		SlotSkillIcon->SetBrushFromTexture(InSkillData.SkillAssetData.SkillIcon);
	}
}

FReply US_QuickSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void US_QuickSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void US_QuickSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool US_QuickSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
