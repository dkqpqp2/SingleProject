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

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMesh> TreeMesh;
};
