// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Animation/BaseAnimNotifyState.h"
#include "HumanAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UHumanAnimNotifyState : public UBaseAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
