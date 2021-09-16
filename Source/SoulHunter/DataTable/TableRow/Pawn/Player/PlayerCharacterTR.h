// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PawnCharacterTR.h"
#include "PlayerCharacterTR.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerCharacterTR
	: public FPawnCharacterTR
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	BoneIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	BattleWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	BattleRunSpeed;
};