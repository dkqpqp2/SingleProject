// Fill out your copyright notice in the Description page of Project Settings.


#include "S_QuickslotComponent.h"

// Sets default values for this component's properties
US_QuickslotComponent::US_QuickslotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void US_QuickslotComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void US_QuickslotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

