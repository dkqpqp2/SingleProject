// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "S_ItemDragDropOperation.generated.h"

class US_ItemBase;
class US_InventoryComponent;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_ItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<US_ItemBase> SourceItem;

	UPROPERTY()
	TObjectPtr<US_InventoryComponent> SourceInventory;

	UPROPERTY()
	TObjectPtr<class US_EquipmentComponent> EquipmentInventory;
};
