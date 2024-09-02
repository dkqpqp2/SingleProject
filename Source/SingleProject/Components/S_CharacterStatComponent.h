// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_CharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /* CurrentHp */);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SINGLEPROJECT_API US_CharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	US_CharacterStatComponent();


	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void SetHp(float NewHp);

	float GetMaxHp() { return MaxHp; }
	float GetCurrentHp() { return CurrentHp; }
	float ApplyDamage(float InDamage);

protected:
	// VisibleInstanceOnly: 배치된 캐릭터마다 각각 다른 Hp를 설정할수있음
	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float MaxHp;

	// Transient: 디스크에 저장할 필요가 없을때 Transient를 사용
	UPROPERTY(Transient,VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

};
