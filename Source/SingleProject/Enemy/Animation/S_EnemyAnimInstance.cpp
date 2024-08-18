// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EnemyAnimInstance.h"
#include "SingleProject/Enemy/S_EnemyBase.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
US_EnemyAnimInstance::US_EnemyAnimInstance()
{
	MovingThreshould = 3.0f;
	JumpingThreshould = 100.0f;
}

void US_EnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Owner = Cast<AS_EnemyBase>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void US_EnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);
	}
}
