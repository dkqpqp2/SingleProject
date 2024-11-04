// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_NewCraftComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCraftUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SINGLEPROJECT_API US_NewCraftComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	FOnCraftUpdated OnCraftUpdated;

	US_NewCraftComponent();

	UFUNCTION(BlueprintCallable)
	void CraftItem(const FName& InCraftItemID);

	UFUNCTION(BlueprintCallable)
	bool IsCraftable(const FName& InCraftItemID);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<class US_InventoryComponent> InventoryReference;

};
