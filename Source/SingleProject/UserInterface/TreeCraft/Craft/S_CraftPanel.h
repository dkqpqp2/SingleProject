// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_CraftPanel.generated.h"

class UButton;
class US_CraftDetailInfo;
class UTreeView;
/**
 *
 */
UCLASS()
class SINGLEPROJECT_API US_CraftPanel : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	//트리뷰 내 아이템이 선택 되었을 때
	UFUNCTION()
	void OnCraftItemClicked(UObject* InItem);

	//트리뷰의 Category가 확장, 접힘 되었을 때 호출
	UFUNCTION()
	void OnCraftItemExpansionChanged(UObject* InItem, bool InIsExpanded);

	//Root 아이템 기준으로 Children을 찾아오는 함수
    UFUNCTION()
    void OnCraftItemGetChildren(UObject* InItem, TArray<UObject*>& Children);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTreeView> CraftItemView;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<US_CraftDetailInfo> CraftDetailInfo;


};
