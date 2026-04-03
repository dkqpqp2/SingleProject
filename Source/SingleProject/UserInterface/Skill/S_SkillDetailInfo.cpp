// Fill out your copyright notice in the Description page of Project Settings.


#include "S_SkillDetailInfo.h"

#include "Character/S_CharacterPlayer.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Data/SkillDataStructs.h"
#include "Components/S_SkillComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "S_GameInstance.h"

void US_SkillDetailInfo::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Learn->OnClicked.AddDynamic(this, &ThisClass::OnClickedSkillBtn);
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

	if (Player->LearnedSkills.Contains(SkillID))
	{
		Btn_Learn->SetIsEnabled(false);
		Btn_Text->SetText(FText::FromString(TEXT("습득완료")));
	}
	else
	{
		Btn_Learn->SetIsEnabled(true);
		Btn_Text->SetText(FText::FromString(TEXT("습득하기")));
	}
}

void US_SkillDetailInfo::OnClickedSkillBtn()
{
	UKismetSystemLibrary::PrintString(this, TEXT("스킬 배우기 버튼 클릭"));
	AS_CharacterPlayer* Player = Cast<AS_CharacterPlayer>(GetOwningPlayerPawn());
	if (Player)
	{
		// SkillPoint는 FText이므로 FText를 FString로 변환 후 정수로 변환
		int32 RequiredSkillPoints = FCString::Atoi(*SkillPoint->GetText().ToString());

		// 스킬 포인트가 충분한 경우
		if (Player->SkillPoint >= RequiredSkillPoints)
		{
			// 스킬 포인트 차감
			Player->SkillPoint -= RequiredSkillPoints;

		

			// 버튼 비활성화 및 텍스트 변경
			Btn_Learn->SetIsEnabled(false);
			MySkillPoint->SetText(FText::AsNumber(Player->SkillPoint));

			US_GameInstance* GameInstance = Cast<US_GameInstance>(GetWorld()->GetGameInstance());
			if (GameInstance)
			{
				const FSkillData* NewSkillData = GameInstance->GetSkillData<FSkillData>(SkillID);
				if (NewSkillData)
				{
					// 스킬 배우기
					Player->LearnSkill(NewSkillData->SkillID);
					// UI 업데이트
					SetSkillData(*NewSkillData); // 스킬 정보 새로고침
					
				}
			}
			
		}
	}
}

void US_SkillDetailInfo::OnSkillPointUpdated()
{

}
