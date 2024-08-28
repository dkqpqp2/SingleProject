// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RunawayFromPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API UBTTask_RunawayFromPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_RunawayFromPlayer();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	bool DetectAndSetTarget(UBehaviorTreeComponent& OwnerComp, APawn* ControllingPawn, FVector Center, float DetectRadius, bool bCheckDotProduct = false, FVector ForwardVector = FVector::ZeroVector);
	void HandleEnemyType(UBehaviorTreeComponent& OwnerComp, AS_EnemyBase* Enemy, APawn* ControllingPawn, FVector Center, float DetectRadius, FVector ForwardVector);
	void RunAwayFromPlayer(UBehaviorTreeComponent& OwnerComp, APawn* ControllingPawn, FVector Center);
};
