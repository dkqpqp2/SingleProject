// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EnemyWolf.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AS_EnemyWolf::AS_EnemyWolf()
{
	GetCapsuleComponent()->InitCapsuleSize(70.0f, 60.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->SetWalkableFloorAngle(50.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()->GravityScale = 1.0f;
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0, 0.0, -70.0), FRotator(0.0, -90.0, 0.0));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("EnemyMesh"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WolfMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimalVarietyPack/Wolf/Meshes/SK_Wolf.SK_Wolf'"));
	if (WolfMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(WolfMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> WolfAnimInstanceClassRef(TEXT("/Game/Character/Blueprints/Enemy/Wolf/AM_Wolf.AM_Wolf_C"));
	if (WolfAnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(WolfAnimInstanceClassRef.Class);
	}

	CurrentEnemyType = EEnemyType::Wolf;
	MaxHp = 150.0f;
}

void AS_EnemyWolf::BeginPlay()
{
	Super::BeginPlay();
	CurrentHp = MaxHp;
}

void AS_EnemyWolf::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}
