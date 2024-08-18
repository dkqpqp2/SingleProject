// Fill out your copyright notice in the Description page of Project Settings.


#include "S_InventoryComponent.h"
#include "Items/S_ItemBase.h"
#include "UserInterface/Equipment/S_EquipmentSlot.h"

US_InventoryComponent::US_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void US_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

US_ItemBase* US_InventoryComponent::FindMatchingItem(US_ItemBase* ItemIn) const
{
	if (ItemIn)
	{
		if (InventoryContents.Contains(ItemIn))
		{
			return ItemIn;
		}
	}
	return nullptr;
}

US_ItemBase* US_InventoryComponent::FindNextItemByID(US_ItemBase* ItemIn) const
{
	if (ItemIn)
	{
		if (const TArray<TObjectPtr<US_ItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
		{
			return *Result;
		}
	}
	return nullptr;
}

US_ItemBase* US_InventoryComponent::FindNextPartialStack(US_ItemBase* ItemIn) const
{
	if (const TArray<TObjectPtr<US_ItemBase>>::ElementType* Result = InventoryContents.FindByPredicate([&ItemIn](const US_ItemBase* InventoryItem)
		{
			return InventoryItem->ID == ItemIn->ID && !InventoryItem->IsFullItemStack();
		}
		))
	{
		return *Result;
	}
	return nullptr;
}

int32 US_InventoryComponent::CalculateWeightAddAmount(US_ItemBase* ItemIn, int32 RequestedAddAmount)
{
	const int32 WeightMaxAddAmount = FMath::FloorToInt((GetWeightCapacity() - InventoryTotalWeight) / ItemIn->GetItemSingleWeight());
	if(WeightMaxAddAmount >= RequestedAddAmount)
	{
		return RequestedAddAmount;
	}
	return WeightMaxAddAmount;
}

int32 US_InventoryComponent::CalculateNumberForFullStack(US_ItemBase* StackableItem, int32 InitialRequestedAddAmount)
{
	const int32 AddAmountToMakeFullStack = StackableItem->ItemNumericData.MaxStackSize - StackableItem->Quantity;
	return FMath::Min(InitialRequestedAddAmount, AddAmountToMakeFullStack);
}


void US_InventoryComponent::RemoveSingleInstanceOfItem(US_ItemBase* ItemIn)
{
	InventoryContents.RemoveSingle(ItemIn);
	OnInventoryUpdated.Broadcast();
}

int32 US_InventoryComponent::RemoveAmountOfItem(US_ItemBase* ItemIn, int32 DesiredAmountToRemove)
{
	const int32 ActualAmountToRemove = FMath::Min(DesiredAmountToRemove, ItemIn->Quantity);

	ItemIn->SetQuantity(ItemIn->Quantity - ActualAmountToRemove);
	InventoryTotalWeight -= ActualAmountToRemove * ItemIn->GetItemSingleWeight();
	OnInventoryUpdated.Broadcast();

	return ActualAmountToRemove;
}

void US_InventoryComponent::SplitExistingStack(US_ItemBase* ItemIn, const int32 AmountToSplit)
{
	if (!(InventoryContents.Num() + 1 > InventorySlotsCapacity))
	{
		RemoveAmountOfItem(ItemIn, AmountToSplit);
		AddNewItem(ItemIn, AmountToSplit);
	}
}

FItemAddResult US_InventoryComponent::HandleNonStackableItems(US_ItemBase* InputItem, int32 RequestedAddAmount)
{
	if (FMath::IsNearlyZero(InputItem->GetItemSingleWeight()) || InputItem->GetItemStackWeight() < 0)
	{
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("{0}을(를) 인벤토리에 추가할 수 없습니다. 아이템의 무게 값이 잘못되었습니다."), InputItem->ItemTextData.Name));
	}

	if (InventoryTotalWeight + InputItem->GetItemSingleWeight() > GetWeightCapacity())
	{
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("{0}을(를) 인벤토리에 추가할 수 없습니다. 아이템이 무게 한도를 초과할 것입니다."), InputItem->ItemTextData.Name));
	}

	if (InventoryContents.Num() + 1 > InventorySlotsCapacity)
	{
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("{0}을(를) 인벤토리에 추가할 수 없습니다. 모든 인벤토리 슬롯이 꽉 찼습니다."), InputItem->ItemTextData.Name));
	}

	AddNewItem(InputItem, 1);
	return FItemAddResult::AddedAll(1, FText::Format(FText::FromString("{0} {1}을(를) 인벤토리에 성공적으로 추가했습니다."), RequestedAddAmount, InputItem->ItemTextData.Name));

}

int32 US_InventoryComponent::HandleStackableItems(US_ItemBase* ItemIn, int32 RequestedAddAmount)
{
	if (RequestedAddAmount <= 0 || FMath::IsNearlyZero(ItemIn->GetItemStackWeight()))
	{
		return 0;
	}
	int32 AmountToDistribute = RequestedAddAmount;

	// (인벤토리에 입력된 아이템이 이미 존재하고, 가득 찬 스택이 아닌지 확인)
	US_ItemBase* ExistingItemStack = FindNextPartialStack(ItemIn);

	// (기존 스택에 아이템 스택을 분배)
	while (ExistingItemStack)
	{
		// (다음 가득 찬 스택을 만들기 위해 필요한 아이템 수량을 계산)
		const int32 AmountToMakeFullStack = CalculateNumberForFullStack(ExistingItemStack, AmountToDistribute);

		// (무게 용량을 기준으로 실제로 들 수 있는 수량을 계산)
		const int32 WeightLimitAddAmount = CalculateWeightAddAmount(ExistingItemStack, AmountToMakeFullStack);

		// (남은 아이템 수량이 무게 용량을 초과하지 않는 한)
		if (WeightLimitAddAmount > 0)
		{

			// (분배할 수량을 조정함)
			ExistingItemStack->SetQuantity(ExistingItemStack->Quantity + WeightLimitAddAmount);
			InventoryTotalWeight += (ExistingItemStack->GetItemSingleWeight() * WeightLimitAddAmount);

			// (분배할 수량을 조정함)
			AmountToDistribute -= WeightLimitAddAmount;

			ItemIn->SetQuantity(AmountToDistribute);

			// (TODO: 무게 용량을 초과하는 상황은 발생하지 않도록 이 로직을 개선해야 함)
			// (최대 무게 용량에 도달하면 더 이상 루프를 실행할 필요가 없음)
			if (InventoryTotalWeight >= InventoryWeightCapacity)
			{
				OnInventoryUpdated.Broadcast();
				return RequestedAddAmount - AmountToDistribute;
			}
		}
		else if (WeightLimitAddAmount <= 0)
		{
			if (AmountToDistribute != RequestedAddAmount)
			{
				// (이 블록은 여러 스택에 아이템을 분배하는 동안 무게 제한이 초과된 경우 실행됨)
				OnInventoryUpdated.Broadcast();
				return RequestedAddAmount - AmountToDistribute;
			}

			return 0;
		}
		if (AmountToDistribute <= 0)
		{
			// (모든 입력 아이템이 기존 스택에 분배됨)
			OnInventoryUpdated.Broadcast();
			return RequestedAddAmount;
		}

		// (입력된 아이템의 유효한 부분 스택이 아직 있는지 확인)
		ExistingItemStack = FindNextPartialStack(ItemIn);
	}

	// (더 이상 부분 스택을 찾을 수 없으면 새 스택을 추가할 수 있는지 확인)
	if (InventoryContents.Num() + 1 <= InventorySlotsCapacity)
	{
		// (인벤토리 무게 용량에 맞게 남은 아이템 수량을 최대한 추가하려고 시도합니다)
		const int32 WeightLimitAddAmount = CalculateWeightAddAmount(ItemIn, AmountToDistribute);
		if (WeightLimitAddAmount > 0)
		{
			// (아직 분배할 아이템이 남아 있지만 무게 제한에 도달한 경우)
			if (WeightLimitAddAmount < AmountToDistribute)
			{
				// (입력된 아이템의 수량을 조정하고, 인벤토리에서 수용할 수 있는 만큼 새로운 스택에 추가함)
				AmountToDistribute -= WeightLimitAddAmount;
				ItemIn->SetQuantity(AmountToDistribute);

				// (일부 스택만 추가되므로 아이템의 복사본을 생성함)
				AddNewItem(ItemIn->CreateItemCopy(), WeightLimitAddAmount);
				return RequestedAddAmount - AmountToDistribute;
			}

			// (그렇지 않으면, 남은 모든 스택을 추가할 수 있음)
			AddNewItem(ItemIn, AmountToDistribute);
			return RequestedAddAmount;
		}

		return RequestedAddAmount - AmountToDistribute;
	}

	return 0;
}

FItemAddResult US_InventoryComponent::HandleAddItem(US_ItemBase* InputItem)
{
	if (GetOwner())
	{
		const int32 InitialRequestedAddAmount = InputItem->Quantity;

		// handle non-stackable items
		if (!InputItem->ItemNumericData.bIsStackable)
		{
			return HandleNonStackableItems(InputItem, InitialRequestedAddAmount);
		}

		// handle stackable
		const int32 StackableAmountAdded = HandleStackableItems(InputItem, InitialRequestedAddAmount);

		if (StackableAmountAdded == InitialRequestedAddAmount)
		{
			return FItemAddResult::AddedAll(InitialRequestedAddAmount, FText::Format(
				FText::FromString("{0} {1}을(를) 인벤토리에 성공적으로 추가했습니다.")
				, InitialRequestedAddAmount
				, InputItem->ItemTextData.Name
			));

		}

		if (StackableAmountAdded < InitialRequestedAddAmount && StackableAmountAdded > 0)
		{
			return FItemAddResult::AddedAll(StackableAmountAdded, FText::Format(
				FText::FromString("일부 수량의 {0}이(가) 인벤토리에 추가되었습니다. 추가된 수량 = {1}")
				, InputItem->ItemTextData.Name
				, StackableAmountAdded
			));
		}

		if (StackableAmountAdded <= 0)
		{
			return FItemAddResult::AddedNone(FText::Format(
				FText::FromString("{0}을(를) 인벤토리에 추가할 수 없습니다. 남은 인벤토리 슬롯이 없거나, 잘못된 아이템입니다.")
				, InputItem->ItemTextData.Name
			));
		}
	}
	check(false);
	return FItemAddResult::AddedNone(FText::FromString("TryAddItem fallthrough error. GetOwner() check somehow failed."));
}

void US_InventoryComponent::AddNewItem(US_ItemBase* Item, const int32 AmountToAdd)
{
	US_ItemBase* NewItem;

	if (Item->bIsCopy || Item->bIsPickup)
	{
		// if the item is already a copy, or is a world pickup.
		NewItem = Item;
		NewItem->ResetItemFlags();
	}
	else
	{
		// used when splitting or dragging to/from another inventory.
		NewItem = Item->CreateItemCopy();
	}

	NewItem->OwningInventory = this;
	NewItem->SetQuantity(AmountToAdd);

	InventoryContents.Add(NewItem);
	InventoryTotalWeight += NewItem->GetItemStackWeight();
	OnInventoryUpdated.Broadcast();
}


