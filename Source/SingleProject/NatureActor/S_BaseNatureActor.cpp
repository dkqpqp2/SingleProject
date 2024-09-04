// Fill out your copyright notice in the Description page of Project Settings.


#include "S_BaseNatureActor.h"

// Sets default values
AS_BaseNatureActor::AS_BaseNatureActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName(TEXT("Tree"));
	RootComponent = Mesh;


	Health = 100.0f;  // 기본 체력
	ShakeIntensity = 5.0f;  // 흔들림 강도
}

// Called when the game starts or when spawned
void AS_BaseNatureActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AS_BaseNatureActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AS_BaseNatureActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Damage : %f"), ActualDamage));
	

	if (ActualDamage > 0.0f)
	{
		Health -= ActualDamage;
		FVector Impulse = FMath::VRand() * ShakeIntensity;
		Mesh->AddImpulse(Impulse, NAME_None, true);
		if (Health <= 0.0f)
		{
			Mesh->AddImpulse(FVector(0, 0, -1) * 500.0f, NAME_None, true);
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Health : %f"), Health));
	return ActualDamage;
}


