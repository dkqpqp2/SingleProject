// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_EnemySpawnPoint.generated.h"

UCLASS()
class SINGLEPROJECT_API AS_EnemySpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AS_EnemySpawnPoint();
protected:
	TObjectPtr<class USceneComponent> Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AS_EnemyBase>> SpawnClass;

	TObjectPtr<class AS_EnemyBase> SpawnEnemy;

	UPROPERTY(EditAnywhere)
	float SpawnTime;

	float AccTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Spawn();

public:
	void ClearSpawnObject();
};
