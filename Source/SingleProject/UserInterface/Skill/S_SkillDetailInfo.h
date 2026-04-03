// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/Skill/S_SkillInfo.h"
#include "S_SkillDetailInfo.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_SkillDetailInfo : public US_SkillInfo
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void SetSkillData(const FSkillData& InSkillData) override;

protected:
	UFUNCTION()
	void OnClickedSkillBtn();

	void OnSkillPointUpdated();
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillDamage;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillHealAmount;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillManaCost;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillCooldownTime;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillDuration;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillType;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillTargetType;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillDescription;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillPoint;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> MySkillPoint;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Btn_Learn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Btn_Text;

	UPROPERTY()
	FName SkillID;
	
};
