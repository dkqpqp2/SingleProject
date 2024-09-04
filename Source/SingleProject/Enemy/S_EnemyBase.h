// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/S_AIInterface.h"
#include "Interfaces/S_AnimationAttackInterface.h"
#include "Interfaces/S_EnemyWidgetInterface.h"
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
class SINGLEPROJECT_API AS_EnemyBase : public ACharacter, public IS_AIInterface, public IS_AnimationAttackInterface, public IS_EnemyWidgetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AS_EnemyBase();

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere)
	EEnemyType CurrentEnemyType;

	float GetMaxHp() { return MaxHp; }
	void SetMaxHp(float InMaxHp) { MaxHp = InMaxHp; }

	TObjectPtr<class AS_EnemySpawnPoint> SpawnPoint;

	void SetSpawnPoint(class AS_EnemySpawnPoint* Point)
	{
		SpawnPoint = Point;
	}

protected:
	virtual void BeginPlay() override;

protected:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHp = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PatrolRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HpBarOffSet)
	float AIHpBarOffSet;

	TObjectPtr<class UAnimInstance> AnimInstance;

	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;
	virtual void AttackByAI() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	virtual void AttackHitCheck();
	virtual void PlayAttackMontage();
	virtual void AttackActionEnd(class UAnimMontage* TargetMontage, bool InProperlyEnded);
	virtual void NotifyAttackActionEnd();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> AttackMontage;

	virtual void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = ItemData)
	TSubclassOf<class AS_Pickup> PickupClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemData)
	TArray<TObjectPtr<UDataTable>> ItemDropTables;

	void DropItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "ture"))
	TObjectPtr<class US_EnemyStatComponent> Stat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "ture"))
	TObjectPtr<class US_AIWidgetComponent> AIHpBar;

	virtual void SetupEnemyWidget(class US_AIUserWidget* InWidget) override;
};
