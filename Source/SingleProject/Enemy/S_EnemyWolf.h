// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/S_EnemyBase.h"
#include "S_EnemyWolf.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API AS_EnemyWolf : public AS_EnemyBase
{
	GENERATED_BODY()
	
public:
	AS_EnemyWolf();

protected:
	virtual void BeginPlay() override;
	void SetDead() override;

	virtual void SetAIAttackDelegate(const FAIEnemyAttackFinished& InOnAttackFinished)override;
	virtual void AttackHitCheck() override;
	virtual void AttackByAI() override;
	virtual void NotifyAttackActionEnd() override;

	FAIEnemyAttackFinished OnAttackFinished;

};
