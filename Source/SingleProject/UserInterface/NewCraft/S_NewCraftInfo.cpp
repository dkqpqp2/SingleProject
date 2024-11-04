// Fill out your copyright notice in the Description page of Project Settings.


#include "S_NewCraftInfo.h"

#include "S_NewCraftMaterialItem.h"
#include "S_GameInstance.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Data/ItemDataStructs.h"

void US_NewCraftInfo::SetCraftItemData(const FCraftItemData& InCraftItemData)
{
	const FItemData* ItemData = US_GameInstance::GetData<FItemData>(this, InCraftItemData.ResultItemData.ID);
	if (ItemData == nullptr)
	{
		return;
	}

	HorizontalBox->ClearChildren();
	Label_ResultName->SetText(ItemData->ItemTextData.Name);
	Img_ResultItem->SetBrushFromTexture(ItemData->ItemAssetData.Icon);
	for (const FCraftMaterialData& MaterialData : InCraftItemData.MaterialItemDataList)
	{
		UUserWidget* MaterialWidget = CreateWidget(this, MaterialWidgetClass);
		if (US_NewCraftMaterialItem* MaterialItem = Cast<US_NewCraftMaterialItem>(MaterialWidget))
		{
			MaterialItem->SetMaterialData(MaterialData);
			HorizontalBox->AddChild(MaterialWidget);
		}
	}
		
}
