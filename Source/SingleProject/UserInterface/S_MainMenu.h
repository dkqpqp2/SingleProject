// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_MainMenu.generated.h"


class AS_CharacterPlayer;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_MainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<AS_CharacterPlayer> PlayerCharacter;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;


};
