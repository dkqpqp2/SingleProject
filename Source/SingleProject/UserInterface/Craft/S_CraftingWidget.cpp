// Fill out your copyright notice in the Description page of Project Settings.


#include "S_CraftingWidget.h"
#include "Data/ItemDataStructs.h"
#include "SingleProject/UserInterface/Craft/S_CraftItemButtonWidget.h"
#include "Items/S_ItemBase.h"
#include "Components/S_InventoryComponent.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"

void US_CraftingWidget::NativeConstruct()
{
    Super::NativeConstruct();
    if (ItemDescriptionText == nullptr || ItemName == nullptr)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("ItemDescriptionText 또는 ItemName이 null입니다."));
    }

}

void US_CraftingWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    PopulateItemList(CraftItemList);
}

void US_CraftingWidget::PopulateItemList(TArray<TObjectPtr<UDataTable>> DataTables)
{
    if (!ItemListScrollBox)
    {
        return;
    }

    for (UDataTable* DataTable : DataTables)
    {
        if (!DataTable)
        {
            continue;
        }

        TArray<FName> RowNames = DataTable->GetRowNames();
        for (const auto& RowName : RowNames)
        {
            FItemData* ItemRow = DataTable->FindRow<FItemData>(RowName, "");
            if (ItemRow)
            {
                //UHorizontalBox* HorizontalBox = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
                US_CraftItemButtonWidget* ItemButton = WidgetTree->ConstructWidget<US_CraftItemButtonWidget>(ButtonListClass);
                if (ItemButton)
                {
                    ItemButton->SetupButton(ItemRow->ID, ItemRow->ItemTextData.Name);
                    ItemListScrollBox->AddChild(ItemButton);
                    
                    CachedItemDataMap.Add(ItemRow->ID, *ItemRow);
                }
                //UTextBlock* ButtonText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
                //UImage* ItemImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());

                //ItemButton->AddChild(HorizontalBox);

                //ItemImage->SetBrushFromTexture(ItemRow->ItemAssetData.Icon);
                //HorizontalBox->AddChild(ItemImage);
                //ButtonText->SetText(FText::FromName(ItemRow->ID));
                //HorizontalBox->AddChild(ButtonText);
            }
        }
    }
    ItemDescriptionText->SetText(FText::FromString(TEXT("조합하고싶은 아이템을 클릭해주세요")));
}

void US_CraftingWidget::OnItemClicked(FName ItemID)
{
    if (CachedItemDataMap.Contains(ItemID))
    {
        const FItemData& ItemData = CachedItemDataMap[ItemID];
        UpdateItemDescription(ItemData);
        FString LogMessage;
        LogMessage += FString::Printf(TEXT("ItemTextData: %s\n"), *ItemData.ItemTextData.Name.ToString());

        for (const FIngredientData& Ingredient : ItemData.Ingredients)
        {
            LogMessage += FString::Printf(TEXT("IngredientID: %s, AmountRequired: %d\n"),
                *Ingredient.IngredientID.ToString(), Ingredient.AmountRequired);
        }

        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, LogMessage);
        OnChangeTextDelegate.Broadcast();
    }
}

void US_CraftingWidget::UpdateItemDescription(const FItemData& ItemData)
{
    if (ItemDescriptionText && ItemName)
    {
        FString DescriptionText;

        // 재료 정보를 표시
        if (InventoryReference)
        {
            for (const FIngredientData& Ingredient : ItemData.Ingredients)
            {
                US_ItemBase* InventoryItem = InventoryReference->FindItemByID(Ingredient.IngredientID);
                int32 ItemQuantity = InventoryItem ? InventoryItem->Quantity : 0;

                DescriptionText = FString::Printf(TEXT("%s: %d / %d\n"),
                    *Ingredient.IngredientID.ToString(), ItemQuantity, Ingredient.AmountRequired);
            }
        }
        // 텍스트 업데이트
        ItemName->SetText(ItemData.ItemTextData.Name);
        ItemDescriptionText->SetText(FText::FromString(DescriptionText));
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Description updated successfully"));
        OnChangeTextDelegate.Broadcast();
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("ItemDescriptionText 또는 ItemName이 null입니다."));
    }
}
