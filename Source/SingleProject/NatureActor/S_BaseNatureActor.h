// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_BaseNatureActor.generated.h"

UCLASS()
class SINGLEPROJECT_API AS_BaseNatureActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AS_BaseNatureActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void StartShaking(float Duration);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 피해를 받을 때 호출되는 함수
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	TObjectPtr<class AS_SpawnNatureActor> SpawnPoint;

	void SetSpawnPoint(class AS_SpawnNatureActor* Point)
	{
		SpawnPoint = Point;
	}
	FTimerHandle DestroyTimerHandle;
protected:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake")
	float ShakeIntensity;
	FVector OriginalLocation;
	
};
