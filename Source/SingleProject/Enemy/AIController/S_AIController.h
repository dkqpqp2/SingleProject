// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "S_AIController.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API AS_AIController : public AAIController
{
	GENERATED_BODY()

public:
	AS_AIController();

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

	void RunAI();
	void StopAI();

protected:
	virtual void OnPossess(APawn* InPawn);

private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
	
};
