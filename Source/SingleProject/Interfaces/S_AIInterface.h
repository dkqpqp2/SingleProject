// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "S_AIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class US_AIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SINGLEPROJECT_API IS_AIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetAIPatrolRadius() = 0;
	virtual float GetAIDetectRange() = 0;
	virtual float GetAIAttackRange() = 0;
	virtual float GetAITurnSpeed() = 0;
};
