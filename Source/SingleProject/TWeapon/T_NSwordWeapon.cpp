// Fill out your copyright notice in the Description page of Project Settings.


#include "T_NSwordWeapon.h"

AT_NSwordWeapon::AT_NSwordWeapon()
{
	WeaponType = EWeaponType::WT_Sword;
	BaseSocketName = TEXT("SwordPosition");
	DrawSocketName = TEXT("WeaponSocket");
}
