
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillDataStructs.generated.h"

UENUM()
enum class ESkillType : uint8
{
	Attack UMETA(DisplayName = "공격스킬"),
	Defense UMETA(DisplayName = "방어스킬"),
	Buff UMETA(DisplayName = "버프스킬"),
	Debuff UMETA(DisplayName = "디버프스킬"),
	Heal UMETA(DisplayName = "회복스킬")
};

UENUM()
enum class ETargetType : uint8
{
	SingleTarget UMETA(DisplayName = "단일"),
	AreaEffect UMETA(DisplayName = "범위"),
	Self UMETA(DisplayName = "자신"),
	Ally UMETA(DisplayName = "아군"),
	Enemy UMETA(DisplayName = "적")
};

USTRUCT(BlueprintType)
struct FSkillStatistics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float Damage; // 스킬 데미지

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	
	float HealAmount; // 회복량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float ManaCost; // 마나 소모량 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float CooldownTime; // 스킬 쿨타임

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float Duration; // 지속 시간
};

USTRUCT(BlueprintType)
struct FSkillTextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	FText Name; // 스킬 이름

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	FText Description; // 스킬 설명
};

USTRUCT(BlueprintType)
struct FSkillAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TObjectPtr<class UTexture2D> SkillIcon; // 스킬 아이콘

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TObjectPtr<class UAnimMontage> SkillAnimation; // 스킬 몽타주

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TObjectPtr<class UNiagaraSystem> SkillEffect; // 스킬 효과
};

USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	FName SkillID;  // 스킬 ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	ESkillType SkillType;  // 스킬 타입

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	ETargetType TargetType;  // 대상 타입

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	FSkillStatistics SkillStatistics;  // 스킬 데미지, 지속 시간, 쿨다운 등

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	FSkillTextData SkillTextData;  // 스킬 이름, 설명

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	FSkillAssetData SkillAssetData;  // 스킬 아이콘, 애니메이션, 효과

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	int32 RequiredSkillPoints; // 스킬 포인트

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	mutable bool bIsLearned; // 스킬을 배웠는지 여부
};