// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "S_AIWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_AIWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void InitWidget() override;
	
};
