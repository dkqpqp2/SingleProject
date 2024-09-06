// Fill out your copyright notice in the Description page of Project Settings.


#include "NatureActor/S_SpawnNatureActor.h"
#include "NatureActor/S_BaseNatureActor.h"

// Sets default values
AS_SpawnNatureActor::AS_SpawnNatureActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	RootComponent = Root;

	SpawnNature = nullptr;
	AccTime = 0.0f;
	SpawnTime = 0.0f;

}

// Called when the game starts or when spawned
void AS_SpawnNatureActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AS_SpawnNatureActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SpawnNature)
	{
		AccTime += DeltaTime;
		if (AccTime >= SpawnTime)
		{
			Spawn();
		}
	}

}

void AS_SpawnNatureActor::Spawn()
{
	if (NatureActorClass.Num() == 0)
	{
		return;
	}

	int32 RandomIndex = FMath::RandRange(0, NatureActorClass.Num() - 1);
	TSubclassOf<AS_BaseNatureActor> RandomSpawnClass = NatureActorClass[RandomIndex];

	if (!IsValid(RandomSpawnClass))
	{
		return;
	}

	FActorSpawnParameters SpawnParam;

	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	SpawnNature = GetWorld()->SpawnActor<AS_BaseNatureActor>(RandomSpawnClass, GetActorLocation(), GetActorRotation(), SpawnParam);
	SpawnNature->SetSpawnPoint(this);
}

void AS_SpawnNatureActor::ClearSpawnObject()
{
	SpawnNature = nullptr;
	AccTime = 0.f;
}

