// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_SpawnNatureActor.generated.h"

UCLASS()
class SINGLEPROJECT_API AS_SpawnNatureActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AS_SpawnNatureActor();

protected:
	TObjectPtr<class USceneComponent> Root;

	UPROPERTY(EditDefaultsOnly, Category = Actor)
	TArray<TSubclassOf<class AS_BaseNatureActor>> NatureActorClass;

	TObjectPtr<class AS_BaseNatureActor> SpawnNature;
	float RandomTime = FMath::RandRange(10.0f, 50.0f);
	UPROPERTY(VisibleAnywhere)
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
