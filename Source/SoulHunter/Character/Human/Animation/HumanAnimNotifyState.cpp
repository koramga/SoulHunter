// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanAnimNotifyState.h"

void UHumanAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AddEndAnimationSequence(TEXT("HeavyLancer_avoid_front"));
	AddEndAnimationSequence(TEXT("HeavyLancer_avoid_left"));
	AddEndAnimationSequence(TEXT("HeavyLancer_avoid_right"));
	AddEndAnimationSequence(TEXT("HeavyLancer_avoid_back"));

	AddEndAnimationSequence(TEXT("HeavyLancer_roll_front"));
	AddEndAnimationSequence(TEXT("HeavyLancer_roll_left"));
	AddEndAnimationSequence(TEXT("HeavyLancer_roll_right"));
	AddEndAnimationSequence(TEXT("HeavyLancer_roll_back"));

	AddEndAnimationSequence(TEXT("Spearman_avoid_front"));
	AddEndAnimationSequence(TEXT("Spearman_avoid_left"));
	AddEndAnimationSequence(TEXT("Spearman_avoid_right"));
	AddEndAnimationSequence(TEXT("Spearman_avoid_back"));

	AddEndAnimationSequence(TEXT("Spearman_roll_front"));
	AddEndAnimationSequence(TEXT("Spearman_roll_left"));
	AddEndAnimationSequence(TEXT("Spearman_roll_right"));
	AddEndAnimationSequence(TEXT("Spearman_roll_back"));

	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
}

void UHumanAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UHumanAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
}