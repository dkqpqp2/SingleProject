// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/S_InteractionInferface.h"
#include "S_InterfaceTestActor.generated.h"

UCLASS()
class SINGLEPROJECT_API AS_InterfaceTestActor : public AActor, public IS_InteractionInferface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AS_InterfaceTestActor();

protected:
	UPROPERTY(EditAnywhere, Category = "Test Actor")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditInstanceOnly, Category = "Test Actor")
	FInteractableData InstanceInteractableData;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void EndInteract() override;
	virtual void Interact(AS_CharacterPlayer* PlayerCharacter) override;
};
