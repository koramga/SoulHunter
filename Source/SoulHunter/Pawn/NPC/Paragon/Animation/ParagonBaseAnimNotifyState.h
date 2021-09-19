// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Animation/NPCBaseAnimNotifyState.h"
#include "ParagonBaseAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UParagonBaseAnimNotifyState : public UNPCBaseAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
