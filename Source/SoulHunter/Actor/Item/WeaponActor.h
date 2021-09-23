// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseActor.h"
#include "WeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API AWeaponActor : public ABaseActor
{
	GENERATED_BODY()

public:
	AWeaponActor();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EWeaponType		m_WeaponType;

public :
	EWeaponType GetWeaponType() const;
};
