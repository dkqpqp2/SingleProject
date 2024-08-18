// Fill out your copyright notice in the Description page of Project Settings.


#include "S_InterfaceTestActor.h"

// Sets default values
AS_InterfaceTestActor::AS_InterfaceTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(Mesh);

}

// Called when the game starts or when spawned
void AS_InterfaceTestActor::BeginPlay()
{
	Super::BeginPlay();
	
	InteractableData = InstanceInteractableData;
}

// Called every frame
void AS_InterfaceTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS_InterfaceTestActor::BeginFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void AS_InterfaceTestActor::EndFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void AS_InterfaceTestActor::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling BeginInteract override on interface test Actor"));
}

void AS_InterfaceTestActor::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling EndInteract override on interface test Actor"));
}

void AS_InterfaceTestActor::Interact(AS_CharacterPlayer* PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Interact override on interface test Actor"));
}

