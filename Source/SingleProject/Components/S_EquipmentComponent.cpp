// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EquipmentComponent.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Items/S_ItemBase.h"
#include "Engine/Engine.h"


US_EquipmentComponent::US_EquipmentComponent()
{

}

void US_EquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void US_EquipmentComponent::EquipItem(const ESlotName SlotName, const FName& SocketName, US_ItemBase* Item)
{
	const FString SlotNameString = StaticEnum<ESlotName>()->GetValueAsString(SlotName);
	if (Item == nullptr)
	{
		return;
	}
	if (IsSlotOccupied(SlotName))
	{
		return;
	}

	EquippedItems.Add(SlotName, Item);

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}

	USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
	if (CharacterMesh && Item->ItemAssetData.Mesh)
	{
		UStaticMeshComponent* ItemMesh = NewObject<UStaticMeshComponent>(Character);
		ItemMesh->SetStaticMesh(Item->ItemAssetData.Mesh);
		ItemMesh->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
		ItemMesh->RegisterComponent();
		EquipmentTotalDamage += Item->ItemStatistics.DamageValue;
		EquipmentTotalArmor += Item->ItemStatistics.ArmorRating;
		SocketEquippedItems.Add(SocketName, ItemMesh);
	}

	OnEquipmentUpdated.Broadcast();
}

void US_EquipmentComponent::UnequipItem(const ESlotName SlotName , const FName& SocketName)
{
	const FString SlotNameString = StaticEnum<ESlotName>()->GetValueAsString(SlotName);
	if (!IsSlotOccupied(SlotName))
	{
		UE_LOG(LogTemp, Warning, TEXT("UnequipItem: Slot %s is not occupied."), *SlotNameString);
		return;
	}

	US_ItemBase* RemovedItem = EquippedItems[SlotName];
	EquippedItems.Remove(SlotName);

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}

	TObjectPtr<UStaticMeshComponent> ItemMesh;
	SocketEquippedItems.RemoveAndCopyValue(SocketName, ItemMesh);
	if (!ItemMesh)
	{
		return;
	}

	ItemMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	ItemMesh->UnregisterComponent();
	EquipmentTotalDamage -= RemovedItem->ItemStatistics.DamageValue;
	EquipmentTotalArmor -= RemovedItem->ItemStatistics.ArmorRating;

	OnEquipmentUpdated.Broadcast();
}

US_ItemBase* US_EquipmentComponent::GetEquippedItem(const ESlotName  SlotName) const
{
	if (IsSlotOccupied(SlotName))
	{
		return EquippedItems[SlotName];
	}
	return nullptr;
}

bool US_EquipmentComponent::IsSlotOccupied(const ESlotName  SlotName) const
{
	bool bIsOccupied = EquippedItems.Contains(SlotName);
	UE_LOG(LogTemp, Warning, TEXT("IsSlotOccupied: Slot %s is %s"), *StaticEnum<ESlotName>()->GetValueAsString(SlotName), bIsOccupied ? TEXT("Occupied") : TEXT("Empty"));
	return bIsOccupied;
}

