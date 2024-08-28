// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RunawayFromPlayer.h"
#include "Enemy/AIController/S_AIController.h"
#include "Interfaces/S_AIInterface.h"
#include "Enemy/S_EnemyBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

UBTTask_RunawayFromPlayer::UBTTask_RunawayFromPlayer()
{
	NodeName = TEXT("RunawayFromPlayer");
}

EBTNodeResult::Type UBTTask_RunawayFromPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}
	FVector Center = ControllingPawn->GetActorLocation();
	FVector ForwardVector = ControllingPawn->GetActorForwardVector();
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	IS_AIInterface* AIPawn = Cast<IS_AIInterface>(ControllingPawn);
	AS_EnemyBase* Enemy = Cast<AS_EnemyBase>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AS_AIController::HomePosKey);
	float PatrolRadius = AIPawn->GetAIPatrolRadius();
	FNavLocation NextRunawayPos;

	if (NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextRunawayPos))
	{
		HandleEnemyType(OwnerComp, Enemy, ControllingPawn, Center, PatrolRadius, ForwardVector);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

bool UBTTask_RunawayFromPlayer::DetectAndSetTarget(UBehaviorTreeComponent& OwnerComp, APawn* ControllingPawn, FVector Center, float DetectRadius, bool bCheckDotProduct, FVector ForwardVector)
{
	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World)
	{
		return false;
	}

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (const auto& OverlapResult : OverlapResults)
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				if (bCheckDotProduct)
				{
					FVector DirectionToPlayer = (Pawn->GetActorLocation() - Center).GetSafeNormal();
					float DotProduct = FVector::DotProduct(ForwardVector, DirectionToPlayer);

					if (DotProduct <= 0.5f)
					{
						continue;
					}
				}

				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AS_AIController::TargetKey, Pawn);
				DrawDebugLine(World, Center, Pawn->GetActorLocation(), FColor::Blue, false, 0.2f);
				return true;
			}
		}
	}

	// 타겟을 찾지 못했을 경우, 블랙보드에서 타겟을 null로 설정
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AS_AIController::TargetKey, nullptr);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);

	return false;
}

void UBTTask_RunawayFromPlayer::HandleEnemyType(UBehaviorTreeComponent& OwnerComp, AS_EnemyBase* Enemy, APawn* ControllingPawn, FVector Center, float DetectRadius, FVector ForwardVector)
{
	bool bTargetDetected = false;
	switch (Enemy->CurrentEnemyType)
	{
	case EEnemyType::Deer:
		bTargetDetected = this->DetectAndSetTarget(OwnerComp, ControllingPawn, Center, DetectRadius, true, ForwardVector);
		if (bTargetDetected)
		{
			this->RunAwayFromPlayer(OwnerComp, ControllingPawn, Center);
		}
		break;
	case EEnemyType::Wolf:
		bTargetDetected = this->DetectAndSetTarget(OwnerComp, ControllingPawn, Center, DetectRadius, false, FVector::ZeroVector);
		break;
	default:
		break;
	}

	// 타겟이 감지되지 않은 경우 Blackboard의 타겟을 초기화
	if (!bTargetDetected)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AS_AIController::TargetKey, nullptr);
	}
}

void UBTTask_RunawayFromPlayer::RunAwayFromPlayer(UBehaviorTreeComponent& OwnerComp, APawn* ControllingPawn, FVector Center)
{
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AS_AIController::TargetKey));
	if (Target)
	{
		FVector DirectionAwayFromPlayer = (Center - Target->GetActorLocation()).GetSafeNormal();
		FVector RunawayLocation = Center + DirectionAwayFromPlayer * 500.0f;  // 500 단위만큼 멀어지는 위치로 설정

		// 블랙보드에 도망 위치 설정
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AS_AIController::RunawayLocationKey, RunawayLocation);

		// 디버그용: 도망가는 경로 표시
		DrawDebugLine(ControllingPawn->GetWorld(), Center, RunawayLocation, FColor::Green, false, 1.0f);
	}
}

