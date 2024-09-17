// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_CraftingWidget.generated.h"

class UItemButtonWidget;

DECLARE_MULTICAST_DELEGATE(FOnChangeText);
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
    TObjectPtr<class UVerticalBox> CratfButtonBox;

    TObjectPtr<class US_CraftButtonWidget> CraftBtn;
    
    TObjectPtr<class US_ItemDescriptionText> ClickedItemDescriptionText;

    TObjectPtr<class US_CraftItemButtonWidget> ItemButton; 

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<class UTextBlock> ItemName;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<class UTextBlock> ItemDescriptionText;

    UPROPERTY()
    TObjectPtr<class US_InventoryComponent> InventoryReference;

    FOnChangeText OnChangeTextDelegate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TObjectPtr<UDataTable>> CraftItemList;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class US_CraftItemButtonWidget> ButtonListClass;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class US_CraftButtonWidget> CraftButtonClass;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class US_ItemDescriptionText> ItemDescriptionTextClass;

    void PopulateItemList(TArray<TObjectPtr<UDataTable>> DataTables);
    FName GetSeletItemButton() const { return SetItemName; }

    void SetSelectItemButton(const FName InItemName);
    bool CanCraftItem(const FItemData& ItemData);

    UFUNCTION()
    void OnItemClicked(FName ItemID);
    void CraftItem(const FItemData& ItemData);

    TMap<FName, FItemData> CachedItemDataMap;
    UFUNCTION()
    void UpdateItemDescription(const FItemData& ItemData);

    UPROPERTY()
    FName SetItemName;

protected:
    virtual void NativeConstruct() override;
    virtual void NativeOnInitialized() override;


};
