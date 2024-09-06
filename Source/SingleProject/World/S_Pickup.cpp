// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Pickup.h"
#include "Items/S_ItemBase.h"
#include "Character/S_CharacterPlayer.h"
#include "Components/S_InventoryComponent.h"


AS_Pickup::AS_Pickup()
{
 		PrimaryActorTick.bCanEverTick = true;

		PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
		PickupMesh->SetSimulatePhysics(true);
		SetRootComponent(PickupMesh);
		PickupMesh->SetEnableGravity(true);

}

void AS_Pickup::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup(US_ItemBase::StaticClass(), ItemQuantity);
}

void AS_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS_Pickup::InitializePickup(const TSubclassOf<US_ItemBase> BaseClass, const int32 InQuantity)
{
	if (ItemDataTable && !DesiredItemID.IsNone())
	{
		const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString());

		ItemReference = NewObject<US_ItemBase>(this, BaseClass);
		ItemReference->ID = ItemData->ID;
		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->ItemQuality = ItemData->ItemQuality;
		ItemReference->ItemNumericData = ItemData->ItemNumericData;
		ItemReference->ItemStatistics = ItemData->ItemStaistics;
		ItemReference->ItemTextData = ItemData->ItemTextData;
		ItemReference->ItemAssetData = ItemData->ItemAssetData;

		ItemReference->ItemNumericData.bIsStackable = ItemData->ItemNumericData.MaxStackSize > 1;
		InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);

		
		PickupMesh->SetStaticMesh(ItemData->ItemAssetData.Mesh);
		
		UpdateInteractableData();
	}
}

void AS_Pickup::InitializeDrop(US_ItemBase* ItemToDrop, int32 InQuantity)
{
	ItemReference = ItemToDrop;

	InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);
	ItemReference->ItemNumericData.Weight = ItemToDrop->GetItemSingleWeight();
	ItemReference->OwningInventory = nullptr;
	
	PickupMesh->SetStaticMesh(ItemToDrop->ItemAssetData.Mesh);

	UpdateInteractableData();
}

void AS_Pickup::UpdateInteractableData()
{
	InstanceInteractableData.InteractableType = EInteractableType::Pickup;
	InstanceInteractableData.Action = ItemReference->ItemTextData.InteractionText;
	InstanceInteractableData.Name = ItemReference->ItemTextData.Name;
	InstanceInteractableData.Quantity = ItemReference->Quantity;

	InteractableData = InstanceInteractableData;
}

void AS_Pickup::BeginFocus()
{
	if (PickupMesh)
	{
		PickupMesh->SetRenderCustomDepth(true);
	}

}

void AS_Pickup::EndFocus()
{
	if (PickupMesh)
	{
		PickupMesh->SetRenderCustomDepth(false);
	}

}

void AS_Pickup::Interact(AS_CharacterPlayer* PlayerCharcater)
{
	if (PlayerCharcater)
	{
		TakePickup(PlayerCharcater);
	}
}

void AS_Pickup::TakePickup(const AS_CharacterPlayer* Taker)
{
	if (!IsPendingKillPending())
	{
		if (ItemReference)
		{
			if (US_InventoryComponent* PlayerInventory = Taker->GetInventory())
			{
				//1. 아이템을 우선 Copy로 생성한다
				US_ItemBase* NewItem = ItemReference->CreateItem(Taker);
				const FItemAddResult AddResult = PlayerInventory->HandleAddItem(NewItem);

				switch (AddResult.OperationResult)
				{
				case EItemAddResult::IAR_NoItemAdded:
					break;
				case EItemAddResult::IAR_PartialAmountItemAdded:
					UpdateInteractableData();
					Taker->UpdateInteractionWidget();
					break;
				case EItemAddResult::IAR_AllItemAdded:
					Destroy();
					break;
				}
				UE_LOG(LogTemp, Warning, TEXT("%s"), *AddResult.ResultMessage.ToString());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Player Inventory Component is Null"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup internal item reference was somehow null"));
		}
	}
}


void AS_Pickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangePropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (ChangePropertyName == GET_MEMBER_NAME_CHECKED(AS_Pickup, DesiredItemID))
	{
		if (ItemDataTable)
		{

			if (const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString()))
			{
				PickupMesh->SetStaticMesh(ItemData->ItemAssetData.Mesh);
			}
		}
	}
}

