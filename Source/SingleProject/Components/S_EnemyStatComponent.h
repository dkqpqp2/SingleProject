// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_EnemyStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAIHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAIHpChangedDelegate, float /*CurrentHp*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SINGLEPROJECT_API US_EnemyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	US_EnemyStatComponent();

	FOnAIHpZeroDelegate OnAIHpZero;
	FOnAIHpChangedDelegate OnAIHpChanged;

	float GetMaxHp() { return MaxHp; }
	float GetCurrentHp() { return CurrentHp; }
	float ApplyDamage(float InDamage);



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetHp(float NewHp);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float MaxHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	TObjectPtr<class AS_EnemyBase> EnemyBase;
		
};
