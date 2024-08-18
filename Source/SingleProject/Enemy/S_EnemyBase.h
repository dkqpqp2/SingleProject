// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/S_AIInterface.h"
#include "S_EnemyBase.generated.h"

UENUM()
enum class EEnemyType : uint8
{
	None UMETA(DisplayName = "없음"),
	Deer UMETA(DisplayName = "사슴"),
	Pig UMETA(DisplayName = "돼지"),
	Fox UMETA(DisplayName = "여우"),
	Wolf UMETA(DisplayName = "늑대")
};

UCLASS()
class SINGLEPROJECT_API AS_EnemyBase : public ACharacter, public IS_AIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AS_EnemyBase();


protected:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	EEnemyType CurrentEnemyType;

	float MaxHp;

	float CurrentHp;

	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PatrolRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnSpeed;

	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;
};
