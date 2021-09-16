// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StatusTableRow.h"
#include "../../../GameInfo.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FClassStatusTableRow
	: public FStatusTableRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	BattleWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	BattleRunSpeed;
};