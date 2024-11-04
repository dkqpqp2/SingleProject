// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_CraftInfo.generated.h"

struct FCraftItemData;
class UImage;
class UTextBlock;
class UScrollBox;
class US_CraftMaterialItem;
/**
 *
 */
UCLASS()
class SINGLEPROJECT_API US_CraftInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetCraftItemData(const FCraftItemData& InCraftItemData);

protected:
	//Result
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Img_ResultItem;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Label_ResultName;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ScrollBox_Material;
	UPROPERTY(EditAnywhere)
	TSubclassOf<US_CraftMaterialItem> MaterialWidgetClass;
};
