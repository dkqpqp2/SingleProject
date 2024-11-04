// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_CraftMaterialItem.generated.h"

class UImage;
class UTextBlock;
struct FCraftMaterialData;
/**
 *
 */
UCLASS()
class SINGLEPROJECT_API US_CraftMaterialItem : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetMaterialData(const FCraftMaterialData& InMaterialData);

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Img_ItemIcon;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Label_ItemName;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Label_Count;
};
