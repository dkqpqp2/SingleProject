// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EnemySpawnPoint.h"

// Sets default values
AS_EnemySpawnPoint::AS_EnemySpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

