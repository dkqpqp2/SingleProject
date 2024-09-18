// Fill out your copyright notice in the Description page of Project Settings.


#include "S_RockActor.h"
#include "NatureActor/S_SpawnNatureActor.h"
#include "World/S_Pickup.h"
#include "Items/S_ItemBase.h"

AS_RockActor::AS_RockActor()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> RockMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Mediterranean_Coast/Meshes/SM_Rock_A.SM_Rock_A'"));
	if (RockMeshRef.Succeeded())
	{
		Mesh->SetStaticMesh(RockMeshRef.Object);
	}

	Health = 200.0f;
	bHasFallen = false;
	bIsShaking = false;
	ShakeDuration = 0.0f;
	ShakeTimeElapsed = 0.0f;
}

void AS_RockActor::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetActorLocation();
}

void AS_RockActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsShaking)
	{
		UpdateShake(DeltaTime);
	}
}

void AS_RockActor::StartShaking(float Duration)
{
	Super::StartShaking(Duration);
	if (bIsShaking) // 이미 흔들리고 있는 경우 중복 호출 방지
	{
		return;
	}
	bIsShaking = true;
	ShakeDuration = Duration;
	ShakeTimeElapsed = 0.0f;
}

void AS_RockActor::StopShaking()
{
	bIsShaking = false;
	SetActorLocation(OriginalLocation);
}

void AS_RockActor::UpdateShake(float DeltaTime)
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

void AS_RockActor::DestroyTimer()
{
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AS_RockActor::DestroyActor, 3.0f, false);
}

void AS_RockActor::DestroyActor()
{
	Destroy();
	DropItem();
	if (SpawnPoint)
	{
		SpawnPoint->ClearSpawnObject();
	}
}

void AS_RockActor::DropItem()
{
	if (!ItemDropTable)
	{
		return;
	}

	TArray<FName> RowNames = ItemDropTable->GetRowNames();
	if (RowNames.Num() == 0)
	{
		return;
	}

	FName SelectRowName = RowNames[FMath::RandRange(0, RowNames.Num() - 1)];

	const FItemData* ItemData = ItemDropTable->FindRow<FItemData>(SelectRowName, "");
	if (ItemData)
	{
		FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 150);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		AS_Pickup* SpawnPickup = GetWorld()->SpawnActor<AS_Pickup>(PickupClass, SpawnLocation, SpawnRotation);
		if (SpawnPickup)
		{
			SpawnPickup->SetItemDataTable(ItemDropTable);
			SpawnPickup->SetInDesiredItemID(SelectRowName);
			int32 Random = FMath::RandRange(2, 4);
			SpawnPickup->InitializePickup(US_ItemBase::StaticClass(), Random);
		}
	}
}
