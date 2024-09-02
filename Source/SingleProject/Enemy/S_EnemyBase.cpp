// Fill out your copyright notice in the Description page of Project Settings.


#include "S_EnemyBase.h"
#include "SingleProject/Enemy/AIController/S_AIController.h"
#include "Enemy/AIController/S_AIController.h"
#include "Items/S_ItemBase.h"
#include "World/S_Pickup.h"
#include "Components/S_EnemyStatComponent.h"
#include "Enemy/UI/S_AIHpBarWidget.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/S_AIWidgetComponent.h"


// Sets default values
AS_EnemyBase::AS_EnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AS_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enmey"));

	Stat = CreateDefaultSubobject<US_EnemyStatComponent>(TEXT("Stat"));


	AIHpBar = CreateDefaultSubobject<US_AIWidgetComponent>(TEXT("AIHpBar"));
	AIHpBar->SetupAttachment(GetMesh());

	static ConstructorHelpers::FClassFinder<UUserWidget> AIHpBarWidgetRef(TEXT("/Game/Character/Blueprints/Enemy/WBP_EnemyHpBar.WBP_EnemyHpBar_C"));
	if (AIHpBarWidgetRef.Class)
	{
		AIHpBar->SetWidgetClass(AIHpBarWidgetRef.Class);
		AIHpBar->SetWidgetSpace(EWidgetSpace::Screen);
		AIHpBar->SetDrawSize(FVector2D(120.0f, 12.0f));
		AIHpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}


	CurrentEnemyType = EEnemyType::None;
}

void AS_EnemyBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->OnAIHpZero.AddUObject(this, &AS_EnemyBase::SetDead);
}

void AS_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	SetMaxHp(MaxHp);
	AIHpBar->SetRelativeLocation(FVector(0.0f, 0.0f, AIHpBarOffSet));
}

// Called every frame
void AS_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AS_EnemyBase::GetAIPatrolRadius()
{
	return PatrolRadius;
}

float AS_EnemyBase::GetAIDetectRange()
{
	return DetectRange;
}

float AS_EnemyBase::GetAIAttackRange()
{
	return AttackRange;
}

float AS_EnemyBase::GetAITurnSpeed()
{
	return TurnSpeed;
}

void AS_EnemyBase::AttackByAI()
{
}

float AS_EnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->ApplyDamage(DamageAmount);

	return DamageAmount;
}

void AS_EnemyBase::AttackHitCheck()
{
	
}

void AS_EnemyBase::PlayAttackMontage()
{
	AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(AttackMontage, 1.0f);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AS_EnemyBase::AttackActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
}

void AS_EnemyBase::AttackActionEnd(UAnimMontage* TargetMontage, bool InProperlyEnded)
{
	NotifyAttackActionEnd();
}

void AS_EnemyBase::NotifyAttackActionEnd()
{
}

void AS_EnemyBase::SetDead()
{
	Cast<AS_AIController>(GetController())->StopAI();
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
}

void AS_EnemyBase::PlayDeadAnimation()
{
	AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage, 1.0f);
}

void AS_EnemyBase::DropItem()
{
	if(ItemDropTables.Num() == 0)
	{
		return;
	}

	UDataTable* SelectedTable = ItemDropTables[FMath::RandRange(0, ItemDropTables.Num() - 1)];
	if (!SelectedTable)
	{
		return;
	}

	TArray<FName> RowNames = SelectedTable->GetRowNames();
	if (RowNames.Num() == 0)
	{
		return;
	}

	FName SelectedRowName = RowNames[FMath::RandRange(0, RowNames.Num() - 1)];

	const FItemData* ItemData = SelectedTable->FindRow<FItemData>(SelectedRowName, "");
	if (ItemData)
	{
		FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 50);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		AS_Pickup* SpawnedPickup = GetWorld()->SpawnActor<AS_Pickup>(PickupClass, SpawnLocation, SpawnRotation);
		if (SpawnedPickup)
		{
			SpawnedPickup->SetItemDataTable(SelectedTable);
			SpawnedPickup->SetInDesiredItemID(SelectedRowName);
			switch (ItemData->ItemType)
			{
			case EItemType::Weapon:
			case EItemType::Armor:
			case EItemType::Helmet:
			case EItemType::Shield:
			case EItemType::Boots:
				SpawnedPickup->InitializePickup(US_ItemBase::StaticClass(), 1);
				break;
			default:
				int32 Random = FMath::RandRange(1, 10);
				SpawnedPickup->InitializePickup(US_ItemBase::StaticClass(), Random);
				break;
			}
			
		}
	}
}

void AS_EnemyBase::SetupEnemyWidget(US_AIUserWidget* InWidget)
{
	US_AIHpBarWidget* HpBarWidget = Cast<US_AIHpBarWidget>(InWidget);
	if (HpBarWidget)
	{
		HpBarWidget->SetMaxHp(Stat->GetMaxHp());
		HpBarWidget->UpdateHpBar(Stat->GetCurrentHp());
		Stat->OnAIHpChanged.AddUObject(HpBarWidget, &US_AIHpBarWidget::UpdateHpBar);
	}
}

