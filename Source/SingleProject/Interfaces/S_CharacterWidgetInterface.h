// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "S_CharacterWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class US_CharacterWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SINGLEPROJECT_API IS_CharacterWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetupCharacterWidget(class US_UserWidget* InUserWidget) = 0;
};
