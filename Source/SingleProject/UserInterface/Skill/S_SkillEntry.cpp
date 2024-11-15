// Fill out your copyright notice in the Description page of Project Settings.


#include "S_SkillEntry.h"
#include "S_SkillInfo.h"
#include "S_GameInstance.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Data/SkillDataStructs.h"

bool US_TreeSkillEntry::HasChildren() const
{
	return TreeChildren.Num() > 0;
}

TArray<class US_TreeSkillEntry*> US_TreeSkillEntry::GetAllChildren() const
{
	return TreeChildren;
}

void US_TreeSkillEntry::AddChild(class US_TreeSkillEntry* InChild)
{
	TreeChildren.AddUnique(InChild);
}

void US_TreeSkillEntry::RemoveChild(class US_TreeSkillEntry* InChild)
{
	TreeChildren.Remove(InChild);
}

void US_TreeSkillEntry::ClearChildren()
{
	TreeChildren.Reset();
}

void US_SkillEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	US_SkillTreeEntry* SkillEntry = Cast<US_SkillTreeEntry>(ListItemObject);
	if(SkillEntry == nullptr)
	{
		return;
	}
	if(SkillEntry->GetSkillData == nullptr)
	{
		return;
	}

	SwitcherTreeSkill->SetActiveWidgetIndex(SkillEntry->TreeDepth);
	if(SkillEntry->HasChildren())
	{
		UpdateCategory(*SkillEntry->GetSkillData);
	}
	else
	{
		UpdateSkill(*SkillEntry->GetSkillData);
	}
	
}

void US_SkillEntry::NativeConstruct()
{
	Super::NativeConstruct();
	Img_Selection->SetVisibility(ESlateVisibility::Collapsed);
}

void US_SkillEntry::NativeDestruct()
{
	Super::NativeDestruct();
}

void US_SkillEntry::NativeOnItemExpansionChanged(bool bIsExpanded)
{
	IUserObjectListEntry::NativeOnItemExpansionChanged(bIsExpanded);

	if (bIsExpanded)
	{
		SwitcherArrow->SetActiveWidget(Img_Expanded);
	}
	else
	{
		SwitcherArrow->SetActiveWidget(Img_Collapsed);
	}
}

void US_SkillEntry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
	US_SkillTreeEntry* Skill = GetListItem<US_SkillTreeEntry>();
	if(Skill == nullptr)
	{
		return;
	}

	if(bIsSelected)
	{
		Img_Selection->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		Img_Selection->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void US_SkillEntry::UpdateCategory(const FSkillData& InSkillData)
{
	FText Name = UEnum::GetDisplayValueAsText(InSkillData.SkillType);
	SkillCategoryName->SetText(Name);
}

void US_SkillEntry::UpdateSkill(const FSkillData& InSkillData)
{
	SkillInfo->SetSkillData(InSkillData);
}
