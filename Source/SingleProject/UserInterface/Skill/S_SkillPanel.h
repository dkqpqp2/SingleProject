// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_SkillPanel.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_SkillPanel : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnSkillClicked(UObject* InSkill);

	UFUNCTION()
	void OnSkillExpansionChanged(UObject* InSkill, bool InIsExpanded);

	UFUNCTION()
	void OnSkillGetChildren(UObject* InSkill, TArray<UObject*>& Children);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTreeView> SkillView;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class US_SkillDetailInfo> SkillDetailInfo;

	UPROPERTY()
	TArray<class US_SkillTreeEntry*> SkillList;
};
