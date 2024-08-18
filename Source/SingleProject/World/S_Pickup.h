// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleProject/Interfaces/S_InteractionInferface.h"
#include "S_Pickup.generated.h"

class US_ItemBase;
class AS_CharacterPlayer;

UCLASS()
class SINGLEPROJECT_API AS_Pickup : public AActor, public IS_InteractionInferface
{
	GENERATED_BODY()
	
public:	


	AS_Pickup();
	
	void InitializePickup(const TSubclassOf<US_ItemBase> BaseClass, const int32 InQuantity);
	void InitializeDrop(US_ItemBase* ItemToDrop, int32 InQuantity);

	TObjectPtr<US_ItemBase> GetItemData() { return ItemReference; }

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void Interact(AS_CharacterPlayer* PlayerCharcater) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup | Components")
	TObjectPtr<class UStaticMeshComponent> PickupMesh;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	TObjectPtr<class UDataTable> ItemDataTable;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	FName DesiredItemID;

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Item Reference")
	TObjectPtr<class US_ItemBase> ItemReference;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	int32 ItemQuantity;

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Interaction")
	FInteractableData InstanceInteractableData;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void UpdateInteractableData();

	void TakePickup(const AS_CharacterPlayer* Taker);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif 

};
