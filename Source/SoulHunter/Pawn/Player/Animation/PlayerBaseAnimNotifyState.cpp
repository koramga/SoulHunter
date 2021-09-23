// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseAnimNotifyState.h"


void UPlayerBaseAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	
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
}

void UPlayerBaseAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UPlayerBaseAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
}
