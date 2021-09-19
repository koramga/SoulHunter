// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ParagonCharacter.h"
#include "ParagonTerraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API AParagonTerraCharacter : public AParagonCharacter
{
	GENERATED_BODY()
	
public :
	AParagonTerraCharacter();

public :
	virtual void NotifyAnimation(EAnimationNotifyType AnimationNotifyType, EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType) override;
};
