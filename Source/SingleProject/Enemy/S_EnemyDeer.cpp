// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EnemyDeer.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AS_EnemyDeer::AS_EnemyDeer()
{

	GetCapsuleComponent()->InitCapsuleSize(70.0f, 50.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->SetWalkableFloorAngle(50.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()->GravityScale = 1.0f;
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0, 0.0, -60.0), FRotator(0.0, -90.0, 0.0));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("EnemyMesh"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DeerMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimalVarietyPack/DeerStagAndDoe/Meshes/SK_DeerDoe.SK_DeerDoe'"));
	if (DeerMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(DeerMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> DeerAnimInstanceClassRef(TEXT("/Game/Character/Blueprints/Enemy/Deer/AM_Deer.AM_Deer_C"));
	if (DeerAnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(DeerAnimInstanceClassRef.Class);
	}

	CurrentEnemyType = EEnemyType::Deer;
	MaxHp = 50.0f;
}

void AS_EnemyDeer::BeginPlay()
{
	Super::BeginPlay();
	SetMaxHp(MaxHp);
	CurrentHp = MaxHp;
}

void AS_EnemyDeer::SetDead()
{
	Super::SetDead();
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);

	DropItem();
}
