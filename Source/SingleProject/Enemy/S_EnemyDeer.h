// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/S_EnemyBase.h"
#include "S_EnemyDeer.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API AS_EnemyDeer : public AS_EnemyBase
{
	GENERATED_BODY()
public:
	AS_EnemyDeer();

protected:
	virtual void BeginPlay() override;
};
