// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "S_SkillEntry.generated.h"

struct FSkillData;

UCLASS()
class US_TreeSkillEntry : public UObject
{
	GENERATED_BODY()

public:
	int32 TreeDepth;

	UPROPERTY()
	TObjectPtr<class US_TreeSkillEntry> RootSkill;

	bool HasChildren() const;
	TArray<class US_TreeSkillEntry*> GetAllChildren() const;
	void AddChild(class US_TreeSkillEntry* InChild);
	void RemoveChild(class US_TreeSkillEntry* InChild);
	void ClearChildren();

private:
	TArray<class US_TreeSkillEntry*> TreeChildren;
	
};

UCLASS()
class US_SkillTreeEntry : public US_TreeSkillEntry
{
	GENERATED_BODY()

public:
	const FSkillData* GetSkillData;
};

// TreeView 를 사용하기위해 필수적으로 상속 받아야함 IUserObjectListEntry;
UCLASS()
class SINGLEPROJECT_API US_SkillEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	// IUserObjectListEntry 있는 함수
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// IUserListEntry 있는 함수
protected:
	virtual void NativeOnItemExpansionChanged(bool bIsExpanded) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> SwitcherTreeSkill;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillCategoryName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> SwitcherArrow;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidget> Img_Collapsed;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidget> Img_Expanded;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class US_SkillInfo> SkillInfo;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Img_Selection;

private:
	void UpdateCategory(const FSkillData& InSkillData);
	void UpdateSkill(const FSkillData& InSkillData);
};
