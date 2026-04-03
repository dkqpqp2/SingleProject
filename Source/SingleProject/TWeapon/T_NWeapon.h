// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TCharacterStat/F_TCharacterStat.h"
#include "Character/S_CharacterPlayer.h"
#include "T_NWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	WT_Sword,	// 검
	WT_Bow,		// 활
	WT_Staff,	// 지팡이
};

UCLASS()
class SINGLEPROJECT_API AT_NWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AT_NWeapon();

public:
	EWeaponType GetWeaponType() { return WeaponType; }
	
public:
	void EquipWeapon(AS_CharacterPlayer* Player);
	void DrawWeapon(USkeletalMeshComponent* Mesh);
	void SheatheWeapon(USkeletalMeshComponent* Mesh);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPoseableMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> WeaponCollision;

	EWeaponType WeaponType;

	F_TCharacterStat WeaponStat;

	FName BaseSocketName;
	FName DrawSocketName;

};
