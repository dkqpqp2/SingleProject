// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_EquipmentComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEquipmentUpdated);
class US_ItemBase;
class UStaticMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SINGLEPROJECT_API US_EquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	FOnEquipmentUpdated OnEquipmentUpdated;

	US_EquipmentComponent();

	void EquipItem(const FString& SlotName, const FName& SocketName, US_ItemBase* Item) ;
	void UnequipItem(const FString& SlotName, const FName& SocketName);
	US_ItemBase* GetEquippedItem(const FString& SlotName) const;
	bool IsSlotOccupied(const FString& SlotName) const;

	float GetEquipmentTotalDamage() const { return EquipmentTotalDamage; };
	float GetEquipmentTotalArmor() const { return EquipmentTotalArmor; };
	TMap<FString, TObjectPtr<US_ItemBase>> GetEquippedItems() const { return EquippedItems; };

	void SetEquipmentTotalDamage(const float NewEquipmentTotalDamage) { EquipmentTotalDamage = NewEquipmentTotalDamage; };
	void SetEquipmentTotalArmor(const float NewEquipmentTotalArmor) { EquipmentTotalArmor = NewEquipmentTotalArmor; };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	float EquipmentTotalDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	float EquipmentTotalArmor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<FString, TObjectPtr<US_ItemBase>> EquippedItems; // 예: "Weapon", "Helmet", "Armor" 같은 키를 사용

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<FName, TObjectPtr<UStaticMeshComponent>> SocketEquippedItems; // 예: "Weapon", "Helmet", "Armor" 같은 키를 사용

};
