// Fill out your copyright notice in the Description page of Project Settings.


#include "S_SkillPanel.h"
#include "S_SkillDetailInfo.h"
#include "S_SkillEntry.h"
#include "S_GameInstance.h"
#include "Components/TreeView.h"
#include "Data/SkillDataStructs.h"
#include "Kismet/GameplayStatics.h"

void US_SkillPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	US_GameInstance* GameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(this));
	if(GameInstance == nullptr)
	{
		return;
	}

	TArray<FName> AllSkillList = GameInstance->GetAllSkillIDs<FSkillData>();
	if(AllSkillList.Num() == 0)
	{
		return;
	}

	TMap<ESkillType, US_SkillTreeEntry*> SkillMap;;
	for(const auto& ID : AllSkillList)
	{
		const FSkillData* Data = GameInstance->GetSkillData<FSkillData>(ID);
		if(Data == nullptr)
		{
			continue;
		}

		US_SkillTreeEntry*& RootSkill = SkillMap.FindOrAdd(Data->SkillType);
		if(RootSkill == nullptr)
		{
			RootSkill = NewObject<US_SkillTreeEntry>();
			RootSkill->GetSkillData = Data;
			RootSkill->TreeDepth = 0;
		}

		US_SkillTreeEntry* Skill = NewObject<US_SkillTreeEntry>();
		Skill->RootSkill = RootSkill;
		Skill->GetSkillData = Data;
		Skill->TreeDepth = RootSkill->TreeDepth + 1;
		RootSkill->AddChild(Skill);
	}

	for(const auto& SkillRoot : SkillMap)
	{
		SkillList.Add(SkillRoot.Value);
	}

	SkillView->SetListItems(SkillList);
	SkillView->CollapseAll();
	SkillView->OnItemClicked().AddUObject(this, &ThisClass::OnSkillClicked);
	SkillView->OnItemExpansionChanged().AddUObject(this, &ThisClass::OnSkillExpansionChanged);
	SkillView->SetOnGetItemChildren(this, &ThisClass::OnSkillGetChildren);
	SkillDetailInfo->SetVisibility(ESlateVisibility::Collapsed);
}

void US_SkillPanel::OnSkillClicked(UObject* InSkill)
{
	US_SkillTreeEntry* Skill = Cast<US_SkillTreeEntry>(InSkill);
	if(Skill == nullptr)
	{
		return;
	}
	if(Skill->GetSkillData == nullptr)
	{
		return;
	}
	if(Skill->RootSkill == nullptr)
	{
		SkillDetailInfo->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	SkillDetailInfo->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	SkillDetailInfo->SetSkillData(*Skill->GetSkillData);
}


void US_SkillPanel::OnSkillExpansionChanged(UObject* InSkill, bool InIsExpanded)
{
	US_SkillTreeEntry* Skill = Cast<US_SkillTreeEntry>(InSkill);
	if(Skill == nullptr)
	{
		return;
	}
}

void US_SkillPanel::OnSkillGetChildren(UObject* InSkill, TArray<UObject*>& Children)
{
	US_SkillTreeEntry* Skill = Cast<US_SkillTreeEntry>(InSkill);
	if (Skill == nullptr)
	{
		return;
	}

	if (Skill->HasChildren())
	{
		for (auto& Child : Skill->GetAllChildren())
		{
			Children.Add(Child);
		}
	}
}
