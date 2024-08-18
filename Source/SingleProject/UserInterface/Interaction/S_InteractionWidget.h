// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_InteractionWidget.generated.h"

class AS_CharacterPlayer;
struct FInteractableData;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_InteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Player Reference")
	TObjectPtr<AS_CharacterPlayer> PlayerReference;

	void UpdateWidget(const FInteractableData* InteractableData) const;

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	TObjectPtr<UTextBlock> NameText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	TObjectPtr<UTextBlock> ActionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	TObjectPtr<UTextBlock> QuantityText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	TObjectPtr<UTextBlock> KeyPressText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	TObjectPtr<UProgressBar> InteractionProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	float CurrentInteractionDuration;

	UFUNCTION(Category = "Interaction Widget | Interactable Data")
	float UpdeteInteractionProgress();

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
};
