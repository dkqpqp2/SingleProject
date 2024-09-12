//#pragma once
//
//#include "CoreMinimal.h"
//#include "Engine/DataTable.h"
//#include "CraftItemRecipe.generated.h"
//
//USTRUCT(BlueprintType)
//struct FCraftingRecipe
//{
//	GENERATED_BODY()
//
//	// 제작할 결과 아이템
//	UPROPERTY(BlueprintReadOnly, Category = "Crafting")
//	TObjectPtr<US_ItemBase> ResultItem;
//
//	// 제작에 필요한 재료 목록과 각 재료의 수량
//	UPROPERTY(BlueprintReadOnly, Category = "Crafting")
//	TMap<TObjectPtr<US_ItemBase>, int32> RequiredMaterials;
//
//	// 제작 시간이 필요한 경우
//	UPROPERTY(BlueprintReadOnly, Category = "Crafting")
//	float CraftingTime;
//};
//
//USTRUCT()
//struct FCraftData : public FTableRowBase
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, Category = "Craft Data")
//	FName ID;
//
//	UPROPERTY(EditAnywhere, Category = "Craft Data")
//	FCraftingRecipe RecipeData;
//};
