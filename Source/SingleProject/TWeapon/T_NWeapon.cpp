// Fill out your copyright notice in the Description page of Project Settings.


#include "T_NWeapon.h"
#include "Character/S_CharacterPlayer.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AT_NWeapon::AT_NWeapon()
{
 	WeaponMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
	WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponCollision = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetupAttachment(RootComponent);
	WeaponCollision->SetCollisionProfileName(TEXT("Weapon"));
	WeaponCollision->bHiddenInGame = false;
}

void AT_NWeapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void AT_NWeapon::EquipWeapon(AS_CharacterPlayer* Player)
{
	if (Player)
	{
		USkeletalMeshComponent* PlayerMesh = Player->GetMesh();

		WeaponMesh->AttachToComponent(PlayerMesh, FAttachmentTransformRules::KeepRelativeTransform, BaseSocketName);
	}
}

void AT_NWeapon::DrawWeapon(USkeletalMeshComponent* Mesh)
{
	if (Mesh)
	{
		WeaponMesh->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, DrawSocketName);
	}
}

void AT_NWeapon::SheatheWeapon(USkeletalMeshComponent* Mesh)
{
	if (Mesh)
	{
		WeaponMesh->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, BaseSocketName);
	}
}




