// Fill out your copyright notice in the Description page of Project Settings.

#include "S_CraftMaterialItem.h"

#include "S_GameInstance.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/ItemDataStructs.h"

void US_CraftMaterialItem::SetMaterialData(const FCraftMaterialData& InMaterialData)
{
	US_GameInstance* GameInstance = US_GameInstance::Get(this);
	if(GameInstance == nullptr)
	{
		return;
	}

	const FItemData* ItemData = GameInstance->GetData<FItemData>(InMaterialData.ID);
	if(ItemData == nullptr)
	{
		return;
	}

	Img_ItemIcon->SetBrushFromTexture(ItemData->ItemAssetData.Icon);
	Label_ItemName->SetText(ItemData->ItemTextData.Name);
	Label_Count->SetText(FText::FromString(FString::FromInt(InMaterialData.RequiredCount)));
}
