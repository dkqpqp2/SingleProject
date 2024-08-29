// Fill out your copyright notice in the Description page of Project Settings.

// Game
#include "S_CharacterPlayer.h"
#include "UserInterface/S_HUD.h"
#include "Components/S_InventoryComponent.h"
#include "Components/S_EquipmentComponent.h"
#include "World/S_Pickup.h"
#include "Items/S_ItemBase.h"

//Engine
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperSpriteComponent.h"
#include "Blueprint/UserWidget.h"

//Input
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "DrawDebugHelpers.h"

AS_CharacterPlayer::AS_CharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	PlayerInventory = CreateDefaultSubobject<US_InventoryComponent>(TEXT("PlayerInventory"));
	PlayerInventory->SetSlotsCapacity(30);
	PlayerInventory->SetWeightCapacity(150.0f);

	PlayerEquipment = CreateDefaultSubobject<US_EquipmentComponent>(TEXT("PlayerEquipment"));
	PlayerEquipment->SetEquipmentTotalDamage(15);
	PlayerEquipment->SetEquipmentTotalArmor(5);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	MiniMapArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MiniMapArm"));
	MiniMapArm->SetupAttachment(RootComponent);
	MiniMapArm->SetWorldRotation(FRotator::MakeFromEuler(FVector(0.0f, -90.0f, 0.0f)));

	SceneCaptureComp = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComp"));
	SceneCaptureComp->SetupAttachment(MiniMapArm);
	SceneCaptureComp->ProjectionType = ECameraProjectionMode::Orthographic;

	MiniMapArrow = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MiniMapArrow"));
	MiniMapArrow->SetupAttachment(RootComponent);

	MiniMapArrow->SetWorldRotation(FRotator::MakeFromEuler(FVector(90.0f, 0.0f, -90.0f)));

	MiniMapArrow->bVisibleInSceneCaptureOnly = true;


	AimingCameraTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("AimingCameraTimeline"));
	DefaultCameraLocation = FVector{ 0.0f, 0.0f, 65.0f };
	AimingCameraLocation = FVector{ 175.0f, 50.0f, 55.0f };
	CameraBoom->SocketOffset = DefaultCameraLocation;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Character/Input/IMC_Default.IMC_Default'"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Character/Input/Actions/IA_Move.IA_Move'"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Character/Input/Actions/IA_Look.IA_Look'"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Character/Input/Actions/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionInteractRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Character/Input/Actions/IA_Interact.IA_Interact'"));
	if (nullptr != InputActionInteractRef.Object)
	{
		InteractAction = InputActionInteractRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionToggleRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Character/Input/Actions/IA_ToggleMenu.IA_ToggleMenu'"));
	if (nullptr != InputActionToggleRef.Object)
	{
		ToggleAction = InputActionToggleRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAimingRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Character/Input/Actions/IA_Aiming.IA_Aiming'"));
	if (nullptr != InputActionAimingRef.Object)
	{
		AimingAction = InputActionAimingRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Character/Input/Actions/IA_Attack.IA_Attack'"));
	if (nullptr != InputActionAttackRef.Object)
	{
		AttackAction = InputActionAttackRef.Object;
	}

	InteractionCheckFrequency = 0.1;
	InteractionCheckDistance = 225.0f;

	BaseEyeHeight = 76.0f;
}

void AS_CharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	HUD = Cast<AS_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	FOnTimelineFloat AimLerpAlphaValue;
	FOnTimelineEvent TimelineFinishedEvent;
	AimLerpAlphaValue.BindUFunction(this, FName("UpdateCameraTimeline"));
	TimelineFinishedEvent.BindUFunction(this, FName("CameraTimelineEnd"));

	if (AimingCameraTimeline && AimingCameraCurve)
	{
		AimingCameraTimeline->AddInterpFloat(AimingCameraCurve, AimLerpAlphaValue);
		AimingCameraTimeline->SetTimelineFinishedFunc(TimelineFinishedEvent);
	}

	if (MiniMapWidgetClass)
	{
		MiniMapWidget = CreateWidget<UUserWidget>(GetWorld(), MiniMapWidgetClass);

		if (MiniMapWidget)
		{
			MiniMapWidget->AddToViewport();
		}
	}
}

void AS_CharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}

}

void AS_CharacterPlayer::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector TraceStart{ FVector::ZeroVector };

	if (!bAiming)
	{
		InteractionCheckDistance = 200.0f;
		TraceStart = GetPawnViewLocation();
	}
	else
	{
		InteractionCheckDistance = 250.0f;
		TraceStart = FollowCamera->GetComponentLocation();
	}

	FVector TraceEnd{ TraceStart + (GetViewRotation().Vector() * InteractionCheckDistance) };

	float LookDirection = FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector());

	if (LookDirection > 0)
	{
		//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 2.0f);

		FCollisionQueryParams QueryParams;

		QueryParams.AddIgnoredActor(this);
		FHitResult TraceHit;

		if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
		{
			if (TraceHit.GetActor()->GetClass()->ImplementsInterface(US_InteractionInferface::StaticClass()))
			{
				if (TraceHit.GetActor() != InteractionData.CurrentInteractable)
				{
					FoundInteractable(TraceHit.GetActor());
					return;
				}
				if (TraceHit.GetActor() == InteractionData.CurrentInteractable)
				{
					return;
				}
			}
		}
	}
	NoInteractableFound();
}

void AS_CharacterPlayer::FoundInteractable(AActor* NewInteractable)
{
	if (IsInteracting())
	{
		EndInteract();
	}
	if (InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}

	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);

	TargetInteractable->BeginFocus();
}

void AS_CharacterPlayer::NoInteractableFound()
{
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		HUD->HideInteractionWidget();

		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
}

void AS_CharacterPlayer::BeginInteract()
{
	PerformInteractionCheck();
	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteract();

			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction,
					this,
					&AS_CharacterPlayer::Interact,
					TargetInteractable->InteractableData.InteractionDuration,
					false
				);
			}
		}
	}
}

void AS_CharacterPlayer::EndInteract()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}
}

void AS_CharacterPlayer::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}

void AS_CharacterPlayer::UpdateInteractionWidget() const
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	}
}

void AS_CharacterPlayer::ToggleMenu()
{
	HUD->ToggleMenu();

	if (HUD->bIsMenuVisible)
	{
		StopAiming();
	}
}

void AS_CharacterPlayer::Aim()
{
	if (!HUD->bIsMenuVisible)
	{
		bAiming = true;
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->MaxWalkSpeed = 200.0f;
		if (AimingCameraTimeline)
		{
			AimingCameraTimeline->PlayFromStart();
		}
	}
}

void AS_CharacterPlayer::StopAiming()
{
	if (bAiming)
	{
		bAiming = false;
		bUseControllerRotationYaw = false;
		HUD->HideCrosshair();
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		if (AimingCameraTimeline)
		{
			AimingCameraTimeline->Reverse();
		}
	}
}

void AS_CharacterPlayer::UpdateCameraTimeline(const float TimelineValue) const
{
	const FVector CameraLocation = FMath::Lerp(DefaultCameraLocation, AimingCameraLocation, TimelineValue);
	CameraBoom->SocketOffset = CameraLocation;
}

void AS_CharacterPlayer::CameraTimelineEnd()
{
	if (AimingCameraTimeline)
	{
		if (AimingCameraTimeline->GetPlaybackPosition() != 0.0f)
		{
			HUD->ShowCrosshair();
		}
	}
}

void AS_CharacterPlayer::DropItem(US_ItemBase* ItemToDrop, const int32 QuantityToDrop)
{
	if (PlayerInventory->FindMatchingItem(ItemToDrop))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const FVector SpawnLocation{ GetActorLocation() + (GetActorForwardVector() * 50.0f) };
		const FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

		const int32 RemovedQuantity = PlayerInventory->RemoveAmountOfItem(ItemToDrop, QuantityToDrop);

		AS_Pickup* Pickup = GetWorld()->SpawnActor<AS_Pickup>(AS_Pickup::StaticClass(), SpawnTransform, SpawnParams);

		Pickup->InitializeDrop(ItemToDrop, RemovedQuantity);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item to drop was somehow null"));
	}
}

void AS_CharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AS_CharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AS_CharacterPlayer::Look);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AS_CharacterPlayer::BeginInteract);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &AS_CharacterPlayer::EndInteract);
	EnhancedInputComponent->BindAction(AimingAction, ETriggerEvent::Started, this, &AS_CharacterPlayer::Aim);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AS_CharacterPlayer::Attack);
	EnhancedInputComponent->BindAction(AimingAction, ETriggerEvent::Completed, this, &AS_CharacterPlayer::StopAiming);
	EnhancedInputComponent->BindAction(ToggleAction, ETriggerEvent::Completed, this, &AS_CharacterPlayer::ToggleMenu);

}

void AS_CharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AS_CharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AS_CharacterPlayer::Attack()
{
	ProcessComboCommand();
}
