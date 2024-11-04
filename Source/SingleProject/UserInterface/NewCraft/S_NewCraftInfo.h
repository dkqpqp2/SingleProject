// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_NewCraftInfo.generated.h"

struct FCraftItemData;


UCLASS()
class SINGLEPROJECT_API US_NewCraftInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetCraftItemData(const FCraftItemData& InCraftItemData);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Img_ResultItem;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Label_ResultName;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> ScrollBox_Material;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> HorizontalBox;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class US_NewCraftMaterialItem> MaterialWidgetClass;
};
