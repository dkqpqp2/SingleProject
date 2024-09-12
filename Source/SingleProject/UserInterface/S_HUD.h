// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "S_HUD.generated.h"


class US_MainMenu;
class US_InteractionWidget;
class US_EquipmentPanel;
struct FInteractableData;
/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API AS_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<US_MainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<US_InteractionWidget> InteractionWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<US_EquipmentPanel> EquipmentWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<US_CraftingWidget> CraftingWidgetClass;

	bool bIsMenuVisible;

	AS_HUD();

	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();


	void ShowCrosshair();
	void HideCrosshair();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;

	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;

	US_CraftingWidget* GetCraftingWidget() const;
protected:
	UPROPERTY()
	TObjectPtr<US_MainMenu> MainMenuWidget;

	UPROPERTY()
	TObjectPtr<US_InteractionWidget> InteractionWidget;

	UPROPERTY()
	TObjectPtr<class UUserWidget> CrosshairWidget;

	UPROPERTY()
	TObjectPtr<class US_EquipmentPanel> EquipmentWidget;

	UPROPERTY()
	TObjectPtr<class US_CraftingWidget> CraftingWidget;

	virtual void BeginPlay() override;
};
