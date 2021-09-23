// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"

AWeaponActor::AWeaponActor()
{
	m_ActorType = EActorType::Weapon;
}

EWeaponType AWeaponActor::GetWeaponType() const
{
	return m_WeaponType;
}