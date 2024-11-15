// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "S_HUD.generated.h"


class US_MainMenu;
class US_InteractionWidget;
class US_EquipmentPanel;
class US_CraftingWidget;
class US_NewCraftPanel;
class US_SkillPanel;
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

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<US_NewCraftPanel> NewCraftWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<US_SkillPanel> SkillPanelWidgetClass;

	bool bIsMenuVisible;
	bool bIsCraftVisible;
	bool bIsSkillMenuVisible;

	AS_HUD();

	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	void DisplayCraft();
	void HideCraft();
	void ToggleCraft();

	void ShowCrosshair();
	void HideCrosshair();

	void ShowSkillPanel();
	void HideSkillPanel();
	void ToggleSkillMenu();

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

	UPROPERTY()
	TObjectPtr<class US_NewCraftPanel> NewCraftPanelWidget;

	UPROPERTY()
	TObjectPtr<US_SkillPanel> SkillPanelWidget;

	virtual void BeginPlay() override;
};
