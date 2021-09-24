// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BaseAnimNotifyStateData.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "BaseAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UBaseAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UBaseAnimNotifyState();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EBaseAnimType	m_BaseAnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	float					m_DeltaTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	TArray<UBaseAnimNotifyStateData*>		m_EndAnimationSequenceData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	TArray<UBaseAnimNotifyStateData*>		m_LoopAnimationSequenceData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	bool					m_HasLoopAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	bool					m_HasEndAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UBaseAnimNotifyStateData* m_SequenceData;

protected:
	void AddLoopAnimationSequence(const FName& Name, const FString& SoundPath = TEXT(""));
	void AddEndAnimationSequence(const FName& Name, const FString& SoundPath = TEXT(""));

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
};
