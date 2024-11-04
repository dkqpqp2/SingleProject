// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "S_CraftItemEntry.generated.h"

class US_CraftInfo;
class UScrollBox;
class UTextBlock;
class UButton;
class UImage;
class UWidgetSwitcher;
class US_CraftMaterialItem;
struct FCraftItemData;


//Entry에 데이터 저장용 사용될 기본 클래스
//이 클래스 하나가 생성되면, 그에 상응하는 Widget도 생김
UCLASS()
class US_TreeItemEntry : public UObject
{
	GENERATED_BODY()

public:
	int32 TreeDepth;

	UPROPERTY()
	TObjectPtr<US_TreeItemEntry> RootItem;

	bool HasChildren() const;
	TArray<US_TreeItemEntry*> GetAllChildren() const;
	void AddChild(US_TreeItemEntry* InChild);
	void RemoveChild(US_TreeItemEntry* InChild);
	void ClearChildren();
private:
	TArray<US_TreeItemEntry*> TreeChildren;
};

UCLASS()
class US_CraftTreeItemEntry : public US_TreeItemEntry
{
	GENERATED_BODY()

public:
	const FCraftItemData* CraftItemData;
};

//트리뷰, 리스트뷰를 구성하기 위해 반드시 상속 되어야 할 IUserObjectListEntry
UCLASS()
class SINGLEPROJECT_API US_CraftItemEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
protected:
	//IUserObjectListEntry
	virtual void NativeOnItemExpansionChanged(bool bIsExpanded) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	//IUserObjectListEntry

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> SwitcherTreeItem;

	//Category
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Label_CategoryName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> SwitcherArrow;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidget> Img_Collapsed;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidget> Img_Expanded;

	//Result
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<US_CraftInfo> CraftInfo;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Img_Selection;
private:
	void UpdateCategory(const FCraftItemData& InCraftItemData);
	void UpdateMaterials(const FCraftItemData& InCraftItemData);
};
