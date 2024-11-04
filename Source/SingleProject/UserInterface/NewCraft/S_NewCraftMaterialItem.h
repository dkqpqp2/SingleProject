// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_NewCraftMaterialItem.generated.h"

struct FCraftMaterialData;

UCLASS()
class SINGLEPROJECT_API US_NewCraftMaterialItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMaterialData(const FCraftMaterialData& InMaterialData);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Img_ItemIcon;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Label_ItemName;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Label_Count;
};
