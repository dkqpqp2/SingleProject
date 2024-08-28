// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RunawayFromPlayer.h"
#include "Enemy/AIController/S_AIController.h"
#include "Interfaces/S_AIInterface.h"
#include "Enemy/S_EnemyBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	AS_EnemyBase* Enemy = Cast<AS_EnemyBase>(ControllingPawn);
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
			Enemy->GetCharacterMovement()->MaxWalkSpeed = 450.0f;
		}
		break;
	case EEnemyType::Wolf:
		bTargetDetected = this->DetectAndSetTarget(OwnerComp, ControllingPawn, Center, DetectRadius, false, FVector::ZeroVector);
		Enemy->GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		break;
	default:
		break;
	}

}

void UBTTask_RunawayFromPlayer::RunAwayFromPlayer(UBehaviorTreeComponent& OwnerComp, APawn* ControllingPawn, FVector Center)
{
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AS_AIController::TargetKey));
	if (Target)
	{
		FVector DirectionAwayFromPlayer = (Center - Target->GetActorLocation()).GetSafeNormal();
		FVector RunawayLocation = Center + DirectionAwayFromPlayer * 1000.0f;  // 500 단위만큼 멀어지는 위치로 설정

		// 블랙보드에 도망 위치 설정
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AS_AIController::RunawayLocationKey, RunawayLocation);
		// 도망 위치로 이동이 완료된 후 정찰을 시작하게 하기 위해 정찰 위치를 도망 위치로 설정
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AS_AIController::PatrolPosKey, RunawayLocation);
		// 디버그용: 도망가는 경로 표시
		DrawDebugLine(ControllingPawn->GetWorld(), Center, RunawayLocation, FColor::Green, false, 1.0f);
	}
}

