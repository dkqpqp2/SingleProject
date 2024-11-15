// Fill out your copyright notice in the Description page of Project Settings.


#include "S_SkillInfo.h"
#include "S_GameInstance.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/SkillDataStructs.h"

void US_SkillInfo::SetSkillData(const FSkillData& InSkillData)
{
	const FSkillData* SkillData = US_GameInstance::GetSkillData<FSkillData>(this, InSkillData.SkillID);
	if(SkillData == nullptr)
	{
		return;
	}

	SkillName->SetText(SkillData->SkillTextData.Name);
	SkillIcon->SetBrushFromTexture(SkillData->SkillAssetData.SkillIcon);
	
}
