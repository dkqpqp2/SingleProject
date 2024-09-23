// Fill out your copyright notice in the Description page of Project Settings.


#include "S_CraftingWidget.h"
#include "Data/ItemDataStructs.h"
#include "SingleProject/UserInterface/Craft/S_CraftItemButtonWidget.h"
#include "Items/S_ItemBase.h"
#include "Components/S_InventoryComponent.h"
#include "UserInterface/Craft/S_ItemDescriptionText.h"
#include "UserInterface/Craft/S_CraftButtonWidget.h"

#include "GameFramework/Character.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

void US_CraftingWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (CraftButtonClass)
    {
        CraftBtn = WidgetTree->ConstructWidget<US_CraftButtonWidget>(CraftButtonClass);
        if (CraftBtn)
        {
            CraftBtn->SetupButton(FText::FromName(TEXT("조합")));
            CraftBtn->SetCraftingWidget(this);
            if (CratfButtonBox)
            {
                CratfButtonBox->AddChild(CraftBtn);
            }
        }
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
                ItemButton = CreateWidget<US_CraftItemButtonWidget>(GetWorld(), ButtonListClass);
                if (ItemButton)
                {
                    ItemButton->SetupButton(ItemRow->ID, ItemRow->ItemTextData.Name);
                    ItemButton->OnCraftItemButtonClicked.BindUObject(this, &US_CraftingWidget::OnItemClicked);
                    ItemListScrollBox->AddChild(ItemButton);
                    CachedItemDataMap.Add(ItemRow->ID, *ItemRow);
                }
            }
        }
    }

}


void US_CraftingWidget::SetSelectItemButton(const FName InItemName)
{
    SetItemName = InItemName;
}

void US_CraftingWidget::OnItemClicked(FName ItemID)
{
    if (CachedItemDataMap.Contains(ItemID))
    {
        SetSelectItemButton(ItemID);

        const FItemData& ItemData = CachedItemDataMap[ItemID];
        UpdateItemDescription(ItemData);
    }
}

void US_CraftingWidget::CraftItem(const FItemData& ItemData)
{
    ACharacter* OwningPlayerCharacter = Cast<ACharacter>(GetOwningPlayerPawn());
    AS_CharacterPlayer* PlayerCharacter = Cast<AS_CharacterPlayer>(OwningPlayerCharacter);
    InventoryReference = OwningPlayerCharacter->FindComponentByClass<US_InventoryComponent>();
    for (const FIngredientData& Ingredient : ItemData.Ingredients)
    {
        US_ItemBase* InventoryItem = InventoryReference->FindItemByID(Ingredient.IngredientID);
        if (InventoryItem)
        {
            InventoryReference->RemoveAmountOfItem(InventoryItem, Ingredient.AmountRequired);
        }
    }
    US_ItemBase* CraftingItem = NewObject<US_ItemBase>();

    CraftingItem->SetCraftItem(PlayerCharacter,ItemData);

    InventoryReference->HandleAddItem(CraftingItem);
    // UI 또는 인벤토리 업데이트
    InventoryReference->OnInventoryUpdated.Broadcast();
   
    if (CachedItemDataMap.Contains(SetItemName))
    {
        const FItemData& UpdatedItemData = CachedItemDataMap[SetItemName];
        UpdateItemDescription(UpdatedItemData);
    }

    OnChangeTextDelegate.Broadcast();
}

bool US_CraftingWidget::CanCraftItem(const FItemData& ItemData)
{
    for (const FIngredientData& Ingredient : ItemData.Ingredients)
    {
        US_ItemBase* InventoryItem = InventoryReference->FindItemByID(Ingredient.IngredientID);
        if (!InventoryItem || InventoryItem->Quantity < Ingredient.AmountRequired)
        {
            return false; // 재료가 부족하거나 인벤토리에 없음
        }
    }
    return true;
}

void US_CraftingWidget::UpdateItemDescription(const FItemData& ItemData)
{
    ACharacter* OwningPlayerCharacter = Cast<ACharacter>(GetOwningPlayerPawn());
    if (ItemDescriptionText)
    {
        FString DescriptionText;

        // 재료 정보를 표시
        InventoryReference = OwningPlayerCharacter->FindComponentByClass<US_InventoryComponent>();
        if (InventoryReference)
        {
            TArray<US_ItemBase*> AllItems = InventoryReference->GetInventoryContents();
            FString InventoryLogMessage;
            if (AllItems.Num() == 0)
            {
                ItemName->SetText(ItemData.ItemTextData.Name);
                ItemDescriptionText->SetText(FText::FromString(TEXT("인벤토리에 재료가 부족합니다")));
                return;
            }
            for (const FIngredientData& Ingredient : ItemData.Ingredients)
            {
                US_ItemBase* InventoryItem = InventoryReference->FindItemByID(Ingredient.IngredientID);
                int32 ItemQuantity = InventoryItem ? InventoryItem->Quantity : 0;

                DescriptionText += FString::Printf(TEXT("%s: %d / %d\n"),
                    *Ingredient.Name.ToString(), ItemQuantity, Ingredient.AmountRequired);
            }

        }
        // 텍스트 업데이트
        ItemName->SetText(ItemData.ItemTextData.Name);
        ItemDescriptionText->SetText(FText::FromString(DescriptionText));
        OnChangeTextDelegate.Broadcast();
    }
    else
    {
    }
}
