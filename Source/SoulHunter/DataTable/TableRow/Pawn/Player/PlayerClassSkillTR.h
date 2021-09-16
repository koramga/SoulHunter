// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "PlayerClassSkillTR.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerClassSkillTR
	: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName			Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FString>	AnimPaths;			//BoneIndex에 종속적
};