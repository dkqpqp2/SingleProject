// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EnemyBase.h"
#include "SingleProject/Enemy/AIController/S_AIController.h"
#include "Enemy/AIController/S_AIController.h"

#include "GameFramework/CharacterMovementComponent.h"
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
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enmey"));

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

void AS_EnemyBase::AttackByAI()
{
}

float AS_EnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	SetDead();

	return DamageAmount;
}

void AS_EnemyBase::SetDead()
{
	Cast<AS_AIController>(GetController())->StopAI();
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
}

void AS_EnemyBase::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage, 1.0f);
}

