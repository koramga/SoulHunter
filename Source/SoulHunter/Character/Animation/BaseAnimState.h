// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BaseAnimStateData.h"
#include "UObject/NoExportTypes.h"
#include "BaseAnimState.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UBaseAnimState : public UObject
{
	GENERATED_BODY()

public:
	UBaseAnimState();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	TMap<EBaseAnimType, UBaseAnimStateData*>	m_mapBaseAnimStateData;

public:
	bool CreateAnimationState(EBaseAnimType BaseAnimType);

public:
	void SetAnimationStateEndCount(EBaseAnimType BaseAnimType, int32 Count);
	void SetStartAnimationState(EBaseAnimType BaseAnimType);
	void AddEndAnimationState(EBaseAnimType BaseAnimType);
	void SetEndAnimationState(EBaseAnimType BaseAnimType);
	void ResetAnimationState(EBaseAnimType BaseAnimType);
	EBaseAnimState GetAnimationState(EBaseAnimType BaseAnimType);

public:
	bool IsFinishAnimationState(EBaseAnimType BaseCharacterAnimationType) const;
	
};
