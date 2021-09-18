// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PawnCharacter.h"
#include "NPCCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API ANPCCharacter : public APawnCharacter
{
	GENERATED_BODY()	

public :
	ANPCCharacter();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	ENPCCharacterType		m_NPCCharacterType;
};
