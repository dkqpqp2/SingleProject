// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "S_TItemData.generated.h"

UENUM(BlueprintType)
enum class ETItemType : uint8 
{ 
	IT_Weapon,		
	IT_Potion,		
	IT_ManaStone,	
};
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_TItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId("S_TItemData", GetFName());
    }
public:
	UPROPERTY(EditAnywhere, Category = Base)
	ETItemType ItemType;

	UPROPERTY(EditAnywhere, Category = Base)
	TObjectPtr<UTexture2D> ItemTexture;
	
	UPROPERTY(EditAnywhere, Category = Base)
	FString ItemName;

	UPROPERTY(EditAnywhere, Category = Base)
	int32 ItemPurchasePrice;

	UPROPERTY(EditAnywhere, Category = Base)
	int32 ItemSalePrice;    
    
};
