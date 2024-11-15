// Fill out your copyright notice in the Description page of Project Settings.


#include "S_SkillDetailInfo.h"

#include "Character/S_CharacterPlayer.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Data/SkillDataStructs.h"
#include "Kismet/KismetSystemLibrary.h"

void US_SkillDetailInfo::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Learn->OnClicked.AddDynamic(this, &ThisClass::OnClickedSkill);
}

void US_SkillDetailInfo::NativeDestruct()
{
	Super::NativeDestruct();
}

void US_SkillDetailInfo::SetSkillData(const FSkillData& InSkillData)
{
	Super::SetSkillData(InSkillData);

	SkillID = InSkillData.SkillID;

	AS_CharacterPlayer* Player = Cast<AS_CharacterPlayer>(GetOwningPlayerPawn());
	
	SkillDamage->SetText(FText::AsNumber(InSkillData.SkillStatistics.Damage));
	SkillHealAmount->SetText(FText::AsNumber(InSkillData.SkillStatistics.HealAmount));
	SkillManaCost->SetText(FText::AsNumber(InSkillData.SkillStatistics.ManaCost));
	SkillCooldownTime->SetText(FText::AsNumber(InSkillData.SkillStatistics.CooldownTime));
	SkillType->SetText(UEnum::GetDisplayValueAsText(InSkillData.SkillType));
	SkillTargetType->SetText(UEnum::GetDisplayValueAsText(InSkillData.TargetType));
	SkillPoint->SetText(FText::AsNumber(InSkillData.RequiredSkillPoints));
	SkillDescription->SetText(InSkillData.SkillTextData.Description);
	MySkillPoint->SetText(FText::AsNumber(Player->SkillPoint));
}

void US_SkillDetailInfo::OnClickedSkill()
{
	UKismetSystemLibrary::PrintString(this, TEXT("스킬 배우기 버튼 클릭"));
	
}

void US_SkillDetailInfo::OnSkillPointUpdated()
{
}
