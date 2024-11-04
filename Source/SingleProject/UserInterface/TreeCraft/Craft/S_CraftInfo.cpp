// Fill out your copyright notice in the Description page of Project Settings.

#include "S_CraftInfo.h"

#include "S_CraftMaterialItem.h"
#include "S_GameInstance.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Data/ItemDataStructs.h"

void US_CraftInfo::SetCraftItemData(const FCraftItemData& InCraftItemData)
{
	//동일한 방법
	// US_GameInstance* GameInstance = US_GameInstance::Get(this);
	// if(GameInstance == nullptr)
	// {
	// 	return;
	// }
	//const FItemData* ItemData = GameInstance->GetData<FItemData>(InCraftItemData.ResultItemData.ID);

	//동일한 방법
	const FItemData* ItemData = US_GameInstance::GetData<FItemData>(this, InCraftItemData.ResultItemData.ID);
	if(ItemData == nullptr)
	{
		return;
	}

	Label_ResultName->SetText(ItemData->ItemTextData.Name);
	Img_ResultItem->SetBrushFromTexture(ItemData->ItemAssetData.Icon);

	ScrollBox_Material->ClearChildren();
	for(const FCraftMaterialData& MaterialData : InCraftItemData.MaterialItemDataList)
	{
		UUserWidget* MaterialWidget = CreateWidget(this, MaterialWidgetClass);
		if(US_CraftMaterialItem* MaterialItem = Cast<US_CraftMaterialItem>(MaterialWidget))
		{
			MaterialItem->SetMaterialData(MaterialData);
			ScrollBox_Material->AddChild(MaterialWidget);
		}
	}
}
