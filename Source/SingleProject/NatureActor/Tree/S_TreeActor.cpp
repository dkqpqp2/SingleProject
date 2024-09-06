// Fill out your copyright notice in the Description page of Project Settings.


#include "S_TreeActor.h"

AS_TreeActor::AS_TreeActor()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TreeMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Mediterranean_Coast/Meshes/SM_Olive_Small_01.SM_Olive_Small_01'"));
	if (TreeMeshRef.Succeeded())
	{
		Mesh->SetStaticMesh(TreeMeshRef.Object);
	}

	Health = 100.0f;
	bHasFallen = false;
	bIsShaking = false;
	ShakeDuration = 0.0f;
	ShakeTimeElapsed = 0.0f;

	FallSpeed = 20.0f;  // 쓰러지는 속도
}

void AS_TreeActor::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetActorLocation();
}

void AS_TreeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShaking)
	{
		UpdateShake(DeltaTime);
	}
	else if (Health <= 0.0f && !bHasFallen)
	{
		Fall();
	}
}

void AS_TreeActor::UpdateShake(float DeltaTime)
{
	ShakeTimeElapsed += DeltaTime;

	if (ShakeTimeElapsed > ShakeDuration)
	{
		StopShaking();
		return;
	}

	FVector NewLocation = OriginalLocation + FVector(0, FMath::Sin(GetWorld()->GetTimeSeconds() * 10.0f) * 5.0f, 0);
	SetActorLocation(NewLocation);
}

void AS_TreeActor::Fall()
{
	bHasFallen = true;
	HandleFall();
	StopShaking();  // 쓰러질 때 흔들림을 멈춤
}

void AS_TreeActor::HandleFall()
{
	// 설정된 회전 값으로 천천히 기울어지게 하기
	TargetRotation = FRotator(-120.0f, 0.0f, 0.0f);  // 나무가 쓰러질 방향
	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), FallSpeed);
	SetActorRotation(NewRotation);
}

void AS_TreeActor::StartShaking(float Duration)
{
	if (bIsShaking) // 이미 흔들리고 있는 경우 중복 호출 방지
	{
		return;
	} 
	bIsShaking = true;
	ShakeDuration = Duration;
	ShakeTimeElapsed = 0.0f;
}

void AS_TreeActor::StopShaking()
{
	bIsShaking = false;
	SetActorLocation(OriginalLocation);
}
