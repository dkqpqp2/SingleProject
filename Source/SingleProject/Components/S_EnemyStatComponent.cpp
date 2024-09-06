
#include "S_EnemyStatComponent.h"
#include "Enemy/S_EnemyBase.h"

US_EnemyStatComponent::US_EnemyStatComponent()
{
	MaxHp = 100.0f;
	CurrentHp = MaxHp;
}

void US_EnemyStatComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHp(MaxHp);
}

float US_EnemyStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnAIHpZero.Broadcast();
	}

	return ActualDamage;
}

void US_EnemyStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);

	OnAIHpChanged.Broadcast(CurrentHp);
}