// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Animation/HumanAnimNotifyState.h"
#include "MannequinBaseAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UMannequinBaseAnimNotifyState : public UHumanAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
};
