// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinBaseAnimNotifyState.h"

void UMannequinBaseAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	AddEndAnimationSequence(TEXT("MTMannequinHeavyLancerCombo1"));
	AddEndAnimationSequence(TEXT("MTMannequinHeavyLancerCombo2"));
	AddEndAnimationSequence(TEXT("MTMannequinHeavyLancerCombo3"));
	AddEndAnimationSequence(TEXT("MTMannequinHeavyLancerCombo4"));

	AddEndAnimationSequence(TEXT("MTMannequinHeavyLancerDash"));

	AddEndAnimationSequence(TEXT("MTMannequinDefence"));
}

void UMannequinBaseAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UMannequinBaseAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
}