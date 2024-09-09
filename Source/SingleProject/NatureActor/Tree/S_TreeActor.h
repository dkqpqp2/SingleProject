// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NatureActor/S_BaseNatureActor.h"
#include "S_TreeActor.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API AS_TreeActor : public AS_BaseNatureActor
{
	GENERATED_BODY()

public:
	AS_TreeActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime)override;
	FVector OriginalLocation;
	bool bHasFallen;
	bool bIsShaking;
	float ShakeDuration;  // 흔들림 지속 시간
	float ShakeTimeElapsed;  // 경과한 흔들림 시간
	FRotator TargetRotation;
	float FallSpeed;  // 쓰러지는 속도 조절

	UPROPERTY(EditDefaultsOnly, Category = ItemData)
	TSubclassOf<class AS_Pickup> PickupClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemData)
	TObjectPtr<UDataTable> ItemDropTable;


public:

	// 흔들림 시작 함수
	virtual void StartShaking(float Duration) override;
	// 흔들림 정지 함수
	void StopShaking();
	void UpdateShake(float DeltaTime);
	void Fall();
	void HandleFall();

	void DestroyTimer();

	UFUNCTION()
	void DestroyActor();

	void DropItem();
};
