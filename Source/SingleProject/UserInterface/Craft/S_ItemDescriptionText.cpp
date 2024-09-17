// Fill out your copyright notice in the Description page of Project Settings.


#include "S_ItemDescriptionText.h"
#include "Components/TextBlock.h"

void US_ItemDescriptionText::UpdateItemDescription(const FString& Name, const FString& Description)
{
	if (ClickedItemName)
	{
		ClickedItemName->SetText(FText::FromString(Name));
	}
	else
	{
		ClickedItemName->SetText(FText::FromString(TEXT("선택된 아이템이 없습니다")));
	}
	if (ClickedItemDescriptionText)
	{
		ClickedItemDescriptionText->SetText(FText::FromString(Description));
	}
	else
	{
		ClickedItemDescriptionText->SetText(FText::FromString(TEXT("아이템을 선택해주세요")));
	}
}
