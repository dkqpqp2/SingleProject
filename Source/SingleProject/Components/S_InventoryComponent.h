// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);

class US_ItemBase;

UENUM()
enum class EItemAddResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName = "아이템이 추가되지 않았음"),
	IAR_PartialAmountItemAdded UMETA(DisplayName = "일부 아이템만 추가됨"),
	IAR_AllItemAdded UMETA(DisplayName = "모든 아이템이 추가됨")
};

USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_BODY()

	FItemAddResult() : 
		ActualAmountAdded(0),
		OperationResult(EItemAddResult::IAR_NoItemAdded),
		ResultMessage(FText::GetEmpty()) 
	{};

	// 인벤토리에 추가된 항목의 실제 양
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 ActualAmountAdded;

	// 항목 추가 작업의 종료 상태를 나타내는 열거형
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	EItemAddResult OperationResult;

	// 결과와 함께 전달할 수 있는 안내 메시지
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	FText ResultMessage;

	static FItemAddResult AddedNone(const FText& ErrorText)
	{
		FItemAddResult AddedNoneResult;
		AddedNoneResult.ActualAmountAdded = 0;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_NoItemAdded;
		AddedNoneResult.ResultMessage = ErrorText;
		return AddedNoneResult;
	};
	static FItemAddResult AddedPartial(const int32 PartialAmountAdded, const FText& ErrorText)
	{
		FItemAddResult AddedPartialResult;
		AddedPartialResult.ActualAmountAdded = PartialAmountAdded;
		AddedPartialResult.OperationResult = EItemAddResult::IAR_PartialAmountItemAdded;
		AddedPartialResult.ResultMessage = ErrorText;
		return AddedPartialResult;
	};
	static FItemAddResult AddedAll(const int32 AmountAdded, const FText& Message)
	{
		FItemAddResult AddedAllResult;
		AddedAllResult.ActualAmountAdded = AmountAdded;
		AddedAllResult.OperationResult = EItemAddResult::IAR_AllItemAdded;
		AddedAllResult.ResultMessage = Message;
		return AddedAllResult;
	};
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SINGLEPROJECT_API US_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	FOnInventoryUpdated OnInventoryUpdated;

	US_InventoryComponent();

	UFUNCTION(Category = "Inventory")
	FItemAddResult HandleAddItem(US_ItemBase* InputItem);

	UFUNCTION(Category = "Inventory")
	US_ItemBase* FindMatchingItem(US_ItemBase* ItemIn) const;
	
	UFUNCTION(Category = "Inventory")
	US_ItemBase* FindNextItemByID(US_ItemBase* ItemIn) const;
	
	UFUNCTION(Category = "Inventory")
	US_ItemBase* FindNextPartialStack(US_ItemBase* ItemIn) const;

	UFUNCTION(Category = "Inventory")
	void RemoveSingleInstanceOfItem(US_ItemBase* ItemIn);
	
	UFUNCTION(Category = "Inventory")
	int32 RemoveAmountOfItem(US_ItemBase* ItemIn, int32 DesiredAmountToRemove);
	
	UFUNCTION(Category = "Inventory")
	void SplitExistingStack(US_ItemBase* ItemIn, const int32 AmountToSplit);

	UFUNCTION(Category = "Inventory")
	float GetInventoryTotalWeight() const { return InventoryTotalWeight; };
	
	UFUNCTION(Category = "Inventory")
	float GetWeightCapacity() const { return InventoryWeightCapacity; };
	
	UFUNCTION(Category = "Inventory")
	int32 GetSlotsCapacity() const { return InventorySlotsCapacity; };
	
	UFUNCTION(Category = "Inventory")
	TArray<US_ItemBase*> GetInventoryContents() const { return InventoryContents; };

	UFUNCTION(Category = "Inventory")
	void SetSlotsCapacity(const int32 NewSlotsCapacity) { InventorySlotsCapacity = NewSlotsCapacity; };

	UFUNCTION(Category = "Inventory")
	void SetWeightCapacity(const float NewWeightCapacity) { InventoryWeightCapacity = NewWeightCapacity; };

	UPROPERTY()
	TObjectPtr<class US_EquipmentSlot> EquipmentSlot;

	UFUNCTION(Category = "Inventory")
	US_ItemBase* FindItemByID(FName ItemID) const;

	TArray<US_ItemBase*> GetAllItems() const;
protected:

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	float InventoryTotalWeight;

	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 InventorySlotsCapacity;
	
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	float InventoryWeightCapacity;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<US_ItemBase>> InventoryContents;

	virtual void BeginPlay() override;

	FItemAddResult HandleNonStackableItems(US_ItemBase* InputItem, int32 RequestedAddAmount);
	int32 HandleStackableItems(US_ItemBase* ItemIn, int32 RequestedAddAmount);
	int32 CalculateWeightAddAmount(US_ItemBase* ItemIn, int32 RequestedAddAmount);
	int32 CalculateNumberForFullStack(US_ItemBase* StackableItem, int32 InitialRequestedAddAmount);

	void AddNewItem(US_ItemBase* Item, const int32 AmountToAdd);

private:
	UPROPERTY()
	TArray<US_ItemBase*> InventoryItems;
};
