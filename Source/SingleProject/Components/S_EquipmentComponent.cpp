// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EquipmentComponent.h"
#include "Items/S_ItemBase.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
US_EquipmentComponent::US_EquipmentComponent()
{

}


// Called when the game starts
void US_EquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void US_EquipmentComponent::EquipItem(const FString& SlotName, US_ItemBase* Item)
{
	if (Item == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("EquipItem: Item is null."));
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Error"));
		return;
	}

	if (IsSlotOccupied(SlotName))
	{
		UE_LOG(LogTemp, Warning, TEXT("EquipItem: Slot %s is already occupied."), *SlotName);
		return;
	}

	EquippedItems.Add(SlotName, Item);

	// 슬롯에 아이템이 장착되었다는 것을 UI나 다른 시스템에 알리기 위한 로직 추가 가능
	UE_LOG(LogTemp, Warning, TEXT("Item %s equipped to slot %s."), *Item->GetName(), *SlotName);
}

void US_EquipmentComponent::UnequipItem(const FString& SlotName)
{
	if (!IsSlotOccupied(SlotName))
	{
		UE_LOG(LogTemp, Warning, TEXT("UnequipItem: Slot %s is not occupied."), *SlotName);
		return;
	}

	US_ItemBase* RemovedItem = EquippedItems[SlotName];
	EquippedItems.Remove(SlotName);

	// 슬롯에서 아이템이 해제되었다는 것을 UI나 다른 시스템에 알리기 위한 로직 추가 가능
	UE_LOG(LogTemp, Warning, TEXT("Item %s unequipped from slot %s."), *RemovedItem->GetName(), *SlotName);
}

US_ItemBase* US_EquipmentComponent::GetEquippedItem(const FString& SlotName) const
{
	if (IsSlotOccupied(SlotName))
	{
		return EquippedItems[SlotName];
	}
	return nullptr;
}

bool US_EquipmentComponent::IsSlotOccupied(const FString& SlotName) const
{
	return EquippedItems.Contains(SlotName);
}

