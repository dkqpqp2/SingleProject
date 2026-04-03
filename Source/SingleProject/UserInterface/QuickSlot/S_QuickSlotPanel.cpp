/// Fill out your copyright notice in the Description page of Project Settings.


#include "S_QuickSlotPanel.h"

#include "S_GameInstance.h"
#include "S_QuickSlot.h"
#include "Character/S_CharacterPlayer.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void US_QuickSlotPanel::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<FName> EmptySkills;  // 빈 배열을 전달
	AddQuickSlotsToBox(LeftSkillBox, EmptySkills);
	AddQuickSlotsToBox(RightSkillBox, EmptySkills);
}

void US_QuickSlotPanel::UpdateQuickSlots(const TArray<FName>& LearnedSkills)
{
	AddQuickSlotsToBox(LeftSkillBox, LearnedSkills);
}
void US_QuickSlotPanel::AddQuickSlotsToBox(UHorizontalBox* SkillBox, const TArray<FName>& LearnedSkills)
{
    if(SkillBox)
    {
        SkillBox->ClearChildren();

        int32 MaxSlot = 4;
        int32 StartIndex = (SkillBox == LeftSkillBox) ? 0 : MaxSlot;  // Left는 0부터, Right는 4부터 시작

        int32 NumSkillsToAdd = FMath::Min(FMath::Max(LearnedSkills.Num() - StartIndex, 0), MaxSlot);;  // 최대 4개까지 추가

        // 배운 스킬 추가
        for(int32 i = 0; i < NumSkillsToAdd; i++)
        {
            US_QuickSlot* NewSlot = CreateWidget<US_QuickSlot>(this, SlotClass);
            if(NewSlot)
            {
                AS_CharacterPlayer* Player = Cast<AS_CharacterPlayer>(GetOwningPlayerPawn());
                if(Player)
                {
                    US_GameInstance* GameInstance = Cast<US_GameInstance>(GetWorld()->GetGameInstance());
                    if(GameInstance)
                    {
                        const FSkillData* SkillData = GameInstance->GetSkillDataByID<FSkillData>(LearnedSkills[StartIndex + i]);
                        if(SkillData)
                        {
                            NewSlot->SetSlotSkillData(*SkillData);
                        }
                    }
                }

                FString KeyText;
                if (SkillBox == LeftSkillBox)
                {
                    // LeftSkillBox는 1, 2, 3, 4 형식으로 표시
                    KeyText = FString::Printf(TEXT("%d"), i + 1);
                }
                else if (SkillBox == RightSkillBox)
                {
                    // RightSkillBox는 F1, F2, F3, F4 형식으로 표시
                    KeyText = FString::Printf(TEXT("F%d"), i + 1);  // F1, F2, F3, F4 형식으로 수정
                }

                NewSlot->SetSkillKeyText(KeyText);

                // 퀵슬롯에 추가
                UHorizontalBoxSlot* NewSlotBox = Cast<UHorizontalBoxSlot>(SkillBox->AddChildToHorizontalBox(NewSlot));

                if (NewSlotBox)
                {
                    NewSlotBox->SetPadding(FMargin(2.f, 0.f));
                }
            }
        }

        // 배운 스킬이 4개 미만인 경우 빈 슬롯을 추가
        for (int32 i = NumSkillsToAdd; i < MaxSlot; i++)
        {
            US_QuickSlot* EmptySlot = CreateWidget<US_QuickSlot>(this, SlotClass);
            if (EmptySlot)
            {
                FString KeyText;
                if (SkillBox == LeftSkillBox)
                {
                    // LeftSkillBox는 1, 2, 3, 4 형식으로 표시
                    KeyText = FString::Printf(TEXT("%d"), i + 1);
                }
                else if (SkillBox == RightSkillBox)
                {
                    // RightSkillBox는 F1, F2, F3, F4 형식으로 표시
                    KeyText = FString::Printf(TEXT("F%d"), i + 1);  // F1, F2, F3, F4 형식으로 수정
                }

                EmptySlot->SetSkillKeyText(KeyText);

                // 빈 슬롯 추가
                UHorizontalBoxSlot* EmptySlotBox = Cast<UHorizontalBoxSlot>(SkillBox->AddChildToHorizontalBox(EmptySlot));

                if (EmptySlotBox)
                {
                    EmptySlotBox->SetPadding(FMargin(2.f, 0.f));
                }
            }
        }
    }
}