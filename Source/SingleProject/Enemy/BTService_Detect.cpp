// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BTService_Detect.h"
#include "Enemy/AIController/S_AIController.h"
#include "Interfaces/S_AIInterface.h"
#include "Enemy/S_EnemyBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}

	FVector Center = ControllingPawn->GetActorLocation();
	FVector ForwardVector = ControllingPawn->GetActorForwardVector();
	UWorld* World = ControllingPawn->GetWorld();

	if (nullptr == World)
	{
		return;
	}

	IS_AIInterface* AIPawn = Cast<IS_AIInterface>(ControllingPawn);
	AS_EnemyBase* Enemy = Cast<AS_EnemyBase>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return;
	}
	float DetectRadius = AIPawn->GetAIDetectRange();
	if (Enemy->CurrentEnemyType == EEnemyType::Deer)
	{
		DetectPlayersInRange(OwnerComp, ControllingPawn, DetectRadius, true);
	}
	else
	{
		DetectPlayersInRange(OwnerComp, ControllingPawn, DetectRadius, false);
	}
	
	Enemy->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void UBTService_Detect::DetectPlayersInRange(UBehaviorTreeComponent& OwnerComp, APawn* ControllingPawn, float DetectRadius, bool bCheckDirection)
{
	FVector Center = ControllingPawn->GetActorLocation();
	FVector ForwardVector = ControllingPawn->GetActorForwardVector();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	bool bResult = ControllingPawn->GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (const FOverlapResult& OverlapResult : OverlapResults)
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				if (bCheckDirection)
				{
					FVector DirectionToPlayer = (Pawn->GetActorLocation() - Center).GetSafeNormal();
					float DotProduct = FVector::DotProduct(ForwardVector, DirectionToPlayer);

					if (DotProduct > 0.5f)
					{
						OwnerComp.GetBlackboardComponent()->SetValueAsObject(AS_AIController::TargetKey, Pawn);
						return;
					}
				}
				else
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(AS_AIController::TargetKey, Pawn);
					return;
				}
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AS_AIController::TargetKey, nullptr);
}