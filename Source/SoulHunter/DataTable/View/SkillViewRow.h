// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillViewRow.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API USkillViewRow : public UObject
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString		m_AnimPath;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		m_ComboCount;
};
