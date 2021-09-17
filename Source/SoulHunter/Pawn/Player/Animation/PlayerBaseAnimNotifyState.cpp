// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseAnimNotifyState.h"


void UPlayerBaseAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AddEndAnimationSequence(TEXT("MTMannequinHeavyLancerCombo1"));
	AddEndAnimationSequence(TEXT("MTMannequinHeavyLancerCombo2"));
	AddEndAnimationSequence(TEXT("MTMannequinHeavyLancerCombo3"));
	AddEndAnimationSequence(TEXT("MTMannequinHeavyLancerCombo4"));

	AddEndAnimationSequence(TEXT("MTMannequinDefence"));

	AddEndAnimationSequence(TEXT("HeavyLancer_avoid_front"));
	AddEndAnimationSequence(TEXT("HeavyLancer_avoid_left"));
	AddEndAnimationSequence(TEXT("HeavyLancer_avoid_right"));
	AddEndAnimationSequence(TEXT("HeavyLancer_avoid_back"));

	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
}

void UPlayerBaseAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UPlayerBaseAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
}
