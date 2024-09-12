// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_CraftingWidget.generated.h"

struct FItemData;
class UItemButtonWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeText, const FItemData&);
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_CraftingWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UScrollBox> ItemListScrollBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> ItemName;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> ItemDescriptionText;

    FOnChangeText OnChangeTextDelegate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TObjectPtr<UDataTable>> CraftItemList;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class US_CraftItemButtonWidget> ButtonListClass;

    void PopulateItemList(TArray<TObjectPtr<UDataTable>> DataTables);

    UFUNCTION()
    void OnItemClicked(FName ItemID);

protected:
    virtual void NativeConstruct() override;
    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void UpdateItemDescription(const FItemData& ItemData);

    UDataTable* FindItemDataTable(FName ItemID);

    TMap<FName, FItemData> CachedItemDataMap;

};
