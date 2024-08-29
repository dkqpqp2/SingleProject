// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/S_CharacterBase.h"
#include "Interfaces/S_InteractionInferface.h"
#include "S_CharacterPlayer.generated.h"

struct FInputActionValue;
class AS_HUD;
class US_ItemBase;

USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f)
	{

	};

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime;
};

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API AS_CharacterPlayer : public AS_CharacterBase, public IS_InteractionInferface
{
	GENERATED_BODY()

public:
	bool bAiming;

	AS_CharacterPlayer();

	// 상호작용
	TObjectPtr<class USpringArmComponent> GetCameraBoom() const { return CameraBoom; };
	TObjectPtr<class UCameraComponent> GetFollowCamera() const { return FollowCamera; };
	bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); };
	TObjectPtr<class US_InventoryComponent> GetInventory() const { return PlayerInventory; };
	TObjectPtr<class US_EquipmentComponent> GetEquipment() const { return PlayerEquipment; };

	void UpdateInteractionWidget() const;

	void DropItem(US_ItemBase* ItemToDrop, const int32 QuantityToDrop);

	UPROPERTY(VisibleAnywhere, Category = "Character | Equipment")
	TObjectPtr<class US_EquipmentPanel> EquipmentPanel;
// 카메라
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "ture"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "ture"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MiniMap)
	TObjectPtr<class USpringArmComponent> MiniMapArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MiniMap)
	TObjectPtr<class USceneCaptureComponent2D> SceneCaptureComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MiniMap)
	TObjectPtr<class UPaperSpriteComponent> MiniMapArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniMap)
	TSubclassOf<UUserWidget> MiniMapWidgetClass;

	TObjectPtr<class UUserWidget> MiniMapWidget;

// 상호작용
protected:
	UPROPERTY()
	TObjectPtr<AS_HUD> HUD;

	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IS_InteractionInferface> TargetInteractable;

	UPROPERTY(VisibleAnywhere, Category = "Character | Inventory")
	TObjectPtr<US_InventoryComponent> PlayerInventory;

	UPROPERTY(VisibleAnywhere, Category = "Character | Equipment")
	TObjectPtr<class US_EquipmentComponent> PlayerEquipment;

	float InteractionCheckFrequency;

	float InteractionCheckDistance;

	FTimerHandle TimerHandle_Interaction;

	FInteractionData InteractionData;

	UPROPERTY(VisibleAnywhere, Category = "Character | Camera")
	FVector DefaultCameraLocation;

	UPROPERTY(VisibleAnywhere, Category = "Character | Camera")
	FVector AimingCameraLocation;

	TObjectPtr<class UTimelineComponent> AimingCameraTimeline;

	UPROPERTY(EditDefaultsOnly, Category = "Aim Timeline")
	TObjectPtr<class UCurveFloat> AimingCameraCurve;

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();


// 입력
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta =(AllowPrivateAccess = "ture"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta =(AllowPrivateAccess = "ture"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta =(AllowPrivateAccess = "ture"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta =(AllowPrivateAccess = "ture"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "ture"))
	TObjectPtr<class UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "ture"))
	TObjectPtr<class UInputAction> ToggleAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "ture"))
	TObjectPtr<class UInputAction> AimingAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "ture"))
	TObjectPtr<class UInputAction> AttackAction;
// 함수
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ToggleMenu();

	void Aim();
	void StopAiming();
	UFUNCTION()
	void UpdateCameraTimeline(const float TimelineValue)const;
	UFUNCTION()
	void CameraTimelineEnd();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void Attack();
};
