// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EnemyBase.h"
#include "SingleProject/Enemy/AIController/S_AIController.h"



#include "Components/CapsuleComponent.h"

// Sets default values
AS_EnemyBase::AS_EnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AS_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	CurrentEnemyType = EEnemyType::None;
}

// Called every frame
void AS_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AS_EnemyBase::GetAIPatrolRadius()
{
	return PatrolRadius;
}

float AS_EnemyBase::GetAIDetectRange()
{
	return DetectRange;
}

float AS_EnemyBase::GetAIAttackRange()
{
	return AttackRange;
}

float AS_EnemyBase::GetAITurnSpeed()
{
	return TurnSpeed;
}

