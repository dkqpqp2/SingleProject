// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EnemyWolf.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Components/S_EnemyStatComponent.h"

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
	MaxHp = Stat->GetMaxHp();
}

void AS_EnemyWolf::BeginPlay()
{
	Super::BeginPlay();
	SetMaxHp(MaxHp);
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

	DropItem();
}

void AS_EnemyWolf::SetAIAttackDelegate(const FAIEnemyAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AS_EnemyWolf::AttackHitCheck()
{
	Super::AttackHitCheck();
	FHitResult OutHitResult;
	// SCENE_QUERY_STAT : Unreal엔진이 제공 하는 분석툴에서 Attack이라는 태그로 우리가 수행하는 작업에 대해서 조사 할수있게 태그를 추가해줌
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float EnemyAttackRange = AttackRange;
	const float EnemyAttackRadius = 30.0f;
	const float EnemyAttackDamage = AttackDamage;
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * EnemyAttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel4, FCollisionShape::MakeSphere(EnemyAttackRadius), Params);
	if (HitDetected)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(EnemyAttackDamage, DamageEvent, GetController(), this);
	}

#if ENABLE_DRAW_DEBUG

	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = EnemyAttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, EnemyAttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);

#endif
}

void AS_EnemyWolf::AttackByAI()
{
	PlayAttackMontage();
}

void AS_EnemyWolf::NotifyAttackActionEnd()
{
	Super::NotifyAttackActionEnd();
	OnAttackFinished.ExecuteIfBound();
}
