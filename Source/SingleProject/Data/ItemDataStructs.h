
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

USTRUCT()
struct FItemStatistics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float ArmorRating;

	UPROPERTY(EditAnywhere)
	float DamageValue;

	UPROPERTY(EditAnywhere)
	float RestorationAmount;

	UPROPERTY(EditAnywhere)
	float SellValue;
	
};

USTRUCT()
struct FItemTextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	FText InteractionText;

	UPROPERTY(EditAnywhere)
	FText UsageText;
};

USTRUCT()
struct FItemNumericData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Weight;

	UPROPERTY(EditAnywhere)
	int32 MaxStackSize;

	UPROPERTY()
	bool bIsStackable;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> Mesh;

};

USTRUCT(BlueprintType)
struct FIngredientData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
	FName IngredientID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
	int32 AmountRequired;
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemStatistics ItemStaistics;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData ItemNumericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData ItemAssetData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	TArray<FIngredientData> Ingredients;
};