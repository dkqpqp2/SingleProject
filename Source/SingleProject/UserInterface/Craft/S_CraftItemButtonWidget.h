// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_CraftItemButtonWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FOnCraftItemClicked, FName);

UCLASS()
class SINGLEPROJECT_API US_CraftItemButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ItemButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FName ItemID;

	void SetupButton(const FName& NewItemID, const FText& ItemName);

	FOnCraftItemClicked OnCraftItemButtonClicked;
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnItemButtonClicked();
};
