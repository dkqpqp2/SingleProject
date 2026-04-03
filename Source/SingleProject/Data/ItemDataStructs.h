
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"


// 아이템 등급
UENUM()
enum class EItemQuality : uint8
{
	Shoddy UMETA(DisplayName = "일반"),
	Common UMETA(DisplayName = "희귀"),
	Masterwork UMETA(DisplayName = "영웅"),
	GrandMaster UMETA(DisplayName = "전설")
};

UENUM()
enum class EItemType : uint8
{
	Weapon UMETA(DisplayName = "무기"),
	Helmet UMETA(DisplayName = "투구"),
	Armor UMETA(DisplayName = "방어구"),
	Shield UMETA(DisplayName = "방패"),
	Spell UMETA(DisplayName = "마법 아이템"),
	Boots UMETA(DisplayName = "신발"),
	Consumable UMETA(DisplayName = "소모 아이템"),
	Quest UMETA(DisplayName = "퀘스트 아이템"),
	Mundane UMETA(DisplayName = "일반 아이템")
};

USTRUCT(BlueprintType)
struct FItemStatistics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ArmorRating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RestorationAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SellValue;
	
};

USTRUCT(BlueprintType)
struct FItemTextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText InteractionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText UsageText;
};

USTRUCT(BlueprintType)
struct FItemNumericData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackSize;

	UPROPERTY(BlueprintReadWrite)
	bool bIsStackable;
};

USTRUCT(BlueprintType)
struct FItemAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> Mesh;

};

USTRUCT(BlueprintType)
struct FIngredientData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
	FName IngredientID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
	int32 AmountRequired;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FItemStatistics ItemStaistics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FItemNumericData ItemNumericData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FItemAssetData ItemAssetData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	TArray<FIngredientData> Ingredients;
};

USTRUCT(BlueprintType)
struct FCraftResultData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;
};

USTRUCT(BlueprintType)
struct FCraftMaterialData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredCount;
};

USTRUCT(BlueprintType)
struct FCraftItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FName ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FText CraftDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FCraftResultData ResultItemData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	TArray<FCraftMaterialData> MaterialItemDataList;
};