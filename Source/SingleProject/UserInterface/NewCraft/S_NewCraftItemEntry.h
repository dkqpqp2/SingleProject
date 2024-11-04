// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "S_NewCraftItemEntry.generated.h"


struct FCraftItemData;

UCLASS()
class US_NewTreeItemEntry : public UObject
{
	GENERATED_BODY()

public:
	int32 TreeDepth;

	UPROPERTY()
	TObjectPtr<class US_NewTreeItemEntry> RootItem;

	bool HasChildren() const;
	TArray<class US_NewTreeItemEntry*> GetAllChildren() const;
	void AddChild(US_NewTreeItemEntry* InChild);
	void RemoveChild(US_NewTreeItemEntry* InChild);
	void ClearChildren();
private:
	TArray<US_NewTreeItemEntry*> TreeChildren;
};

UCLASS()
class US_NewCraftTreeItemEntry : public US_NewTreeItemEntry
{
	GENERATED_BODY()

public:
	const FCraftItemData* CraftItemData;
};


UCLASS()
class SINGLEPROJECT_API US_NewCraftItemEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	virtual void NativeOnItemExpansionChanged(bool bIsExpanded) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> SwitcherTreeItem;


	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Label_CategoryName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> SwitcherArrow;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidget> Img_Collapsed;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidget> Img_Expanded;

	//Result
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class US_NewCraftInfo> CraftInfo;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Img_Selection;
private:
	void UpdateCategory(const FCraftItemData& InCraftItemData);
	void UpdateMaterials(const FCraftItemData& InCraftItemData);
};
