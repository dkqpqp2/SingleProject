// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_DragItemVisual.generated.h"

class UBorder;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_DragItemVisual : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "Drag Item Visual", meta = (BindWidget))
	TObjectPtr<UBorder> ItemBorder;

	UPROPERTY(VisibleAnywhere, Category = "Drag Item Visual", meta = (BindWidget))
	TObjectPtr<UImage>ItemIcon;

	UPROPERTY(VisibleAnywhere, Category = "Drag Item Visual", meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemQuantity;
};
