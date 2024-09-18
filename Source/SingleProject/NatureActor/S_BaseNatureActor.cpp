// Fill out your copyright notice in the Description page of Project Settings.


#include "S_BaseNatureActor.h"
#include "NatureActor/Tree/S_TreeActor.h"
#include "Data/ItemDataStructs.h"
#include "World/S_Pickup.h"
#include "NatureActor/Tree/S_TreeActor.h"
#include "NatureActor/Rock/S_RockActor.h"


// Sets default values
AS_BaseNatureActor::AS_BaseNatureActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Health = 100.0f;
	ShakeIntensity = 10.0f;
}

// Called when the game starts or when spawned
void AS_BaseNatureActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AS_BaseNatureActor::StartShaking(float Duration)
{
}

// Called every frame
void AS_BaseNatureActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AS_BaseNatureActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Damage : %f"), ActualDamage));
	

	if (ActualDamage > 0.0f)
	{
		Health -= ActualDamage;
		if (Health > 0.0f)
		{
			// 흔들림 시작
			if (AS_TreeActor* TreeActor = Cast<AS_TreeActor>(this))
			{
				TreeActor->StartShaking(1.0f);  // 1초 동안 흔들림
			}
			else if (AS_RockActor* RockActor = Cast<AS_RockActor>(this))
			{
				RockActor->StartShaking(0.5f);
			}
		}
		else
		{
			// 체력이 0 이하로 떨어지면 쓰러짐 처리
			if (AS_TreeActor* TreeActor = Cast<AS_TreeActor>(this))
			{
				TreeActor->Fall();
				TreeActor->DestroyTimer();
			}
			else if (AS_RockActor* RockActor = Cast<AS_RockActor>(this))
			{
				RockActor->DestroyTimer();
			}
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Health : %f"), Health));
	return ActualDamage;
}


