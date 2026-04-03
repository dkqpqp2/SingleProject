// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/SkillDataStructs.h"
#include "Data/ItemDataStructs.h"
#include "S_QuickSlot.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_QuickSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere, Category = "QuickSlot")
	FName SlotID;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere, Category = "QuickSlot")
	TObjectPtr<UImage> SlotSkillIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuickSlot")
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuickSlot")
	FSkillData SkillData;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* KeyText;

	void SetSkillKeyText(const FString& InKeyText);
	void SetSlotSkillData(const FSkillData& InSkillData);

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
