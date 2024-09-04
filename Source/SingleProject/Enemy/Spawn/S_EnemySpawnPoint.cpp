// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EnemySpawnPoint.h"
#include "Enemy/S_EnemyBase.h"

// Sets default values
AS_EnemySpawnPoint::AS_EnemySpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	RootComponent = Root;

	//Root->bVisualizeComponent = true;

	SpawnEnemy = nullptr;
	AccTime = 0.f;
	SpawnTime = 0.f;
}

// Called when the game starts or when spawned
void AS_EnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AS_EnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SpawnEnemy)
	{
		AccTime += DeltaTime;
		if (AccTime >= SpawnTime)
		{
			Spawn();
		}
	}

}

void AS_EnemySpawnPoint::Spawn()
{
	if (SpawnClass.Num() == 0)
	{
		return;
	}

	int32 RandomIndex = FMath::RandRange(0, SpawnClass.Num() - 1);
	TSubclassOf<AS_EnemyBase> RandomSpawnClass = SpawnClass[RandomIndex];

	if (!IsValid(RandomSpawnClass))
	{
		return;
	}

	FActorSpawnParameters SpawnParam;

	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	SpawnEnemy = GetWorld()->SpawnActor<AS_EnemyBase>(RandomSpawnClass, GetActorLocation(), GetActorRotation(), SpawnParam);
	SpawnEnemy->SetSpawnPoint(this);
}

void AS_EnemySpawnPoint::ClearSpawnObject()
{
	SpawnEnemy = nullptr;
	AccTime = 0.f;
}

