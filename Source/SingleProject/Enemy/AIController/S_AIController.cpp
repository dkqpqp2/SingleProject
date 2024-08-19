// Fill out your copyright notice in the Description page of Project Settings.


#include "S_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"	

const FName AS_AIController::HomePosKey(TEXT("HomePos"));
const FName AS_AIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AS_AIController::TargetKey(TEXT("Target"));

AS_AIController::AS_AIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/Character/Blueprints/Enemy/BB_Enemy.BB_Enemy'"));
	if (BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/Character/Blueprints/Enemy/BT_Enemy.BT_Enemy'"));
	if (BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AS_AIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AS_AIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AS_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
