// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EquipmentComponent.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
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

void US_EquipmentComponent::EquipItem(const ESlotName SlotName, const FName& SocketName, US_ItemBase* Item)
{
	const FString SlotNameString = StaticEnum<ESlotName>()->GetValueAsString(SlotName);
	if (Item == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("EquipItem: Item is null."));
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Error"));
		return;
	}

	if (IsSlotOccupied(SlotName))
	{
		UE_LOG(LogTemp, Warning, TEXT("EquipItem: Slot %s is already occupied."), *SlotNameString);
		return;
	}

	EquippedItems.Add(SlotName, Item);
	
	// 슬롯에 아이템이 장착되었다는 것을 UI나 다른 시스템에 알리기 위한 로직 추가 가능
	UE_LOG(LogTemp, Warning, TEXT("Item %s equipped to slot %s."), *Item->GetName(), *SlotNameString);

	//2. 기존의 ItemBase의 EquipToSocket 함수를 옮겨옴
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

		SocketEquippedItems.Add(SocketName, ItemMesh);
	}

	//3. EquipmentPanel 에 변경된 내용을 Update하기 위한 딜리게이트
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

	// 슬롯에서 아이템이 해제되었다는 것을 UI나 다른 시스템에 알리기 위한 로직 추가 가능
	UE_LOG(LogTemp, Warning, TEXT("Item %s unequipped from slot %s."), *RemovedItem->GetName(), *SlotNameString);

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
	return EquippedItems.Contains(SlotName);
}

