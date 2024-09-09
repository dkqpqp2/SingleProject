// Fill out your copyright notice in the Description page of Project Settings.


#include "S_CraftingWidget.h"
#include "Data/ItemDataStructs.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"

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
		for (auto& RowName : RowNames)
		{
			FItemData* ItemRow = DataTable->FindRow<FItemData>(RowName, "");
			if (ItemRow)
			{
				UButton* ItemButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
				UTextBlock* ButtonText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

				// 아이템 이름 텍스트 설정
				ButtonText->SetText(FText::FromName(ItemRow->ID));
				ItemButton->AddChild(ButtonText);


				// ScrollBox에 버튼 추가
				ItemListScrollBox->AddChild(ItemButton);
			}
		}
	}
}

void US_CraftingWidget::OnItemClicked(FItemData SelectedItem)
{
	if (!ItemDescriptionText)
	{
		return;
	}


	// 재료 정보를 표시
	FString Description = "아이템: " + SelectedItem.ItemTextData.Name.ToString() + "\n";
	//Description += "필요한 재료: " + SelectedItem.ItemTextData; // 이곳에 실제 재료 정보가 있어야 함

	// 텍스트 업데이트
	ItemDescriptionText->SetText(FText::FromString(Description));
}
