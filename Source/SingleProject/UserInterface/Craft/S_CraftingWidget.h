// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_CraftingWidget.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_CraftingWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    // ScrollBox와 Text 같은 위젯에 대한 참조
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UScrollBox> ItemListScrollBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> ItemDescriptionText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> CraftButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CraftItemData)
    TArray<TObjectPtr<UDataTable>> CraftItemList;

    void PopulateItemList(TArray<TObjectPtr<UDataTable>> DataTables);

    void OnItemClicked(FItemData SelectedItem);

	
};
