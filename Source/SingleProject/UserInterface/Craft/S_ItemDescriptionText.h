// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_ItemDescriptionText.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_ItemDescriptionText : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> ClickedItemName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> ClickedItemDescriptionText;
	
	UFUNCTION()
	void UpdateItemDescription(const FString& Name, const FString& Description);
};
