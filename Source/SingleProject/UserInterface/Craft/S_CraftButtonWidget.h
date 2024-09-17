// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_CraftButtonWidget.generated.h"

class US_CraftingWidget;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_CraftButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CraftButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CraftText;

	UPROPERTY()
	TObjectPtr<class US_InventoryComponent> InventoryReference;

	void SetCraftingWidget(US_CraftingWidget* InCraftingWidget) { CraftingWidget = InCraftingWidget; }


	void SetupButton(const FText& InText);

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnItemButtonClicked();

	UPROPERTY()
	TObjectPtr<class US_CraftingWidget> CraftingWidget;
};
