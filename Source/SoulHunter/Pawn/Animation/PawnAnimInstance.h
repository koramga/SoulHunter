// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "PawnAnimState.h"
#include "PawnAnimCombo.h"
#include "Animation/AnimInstance.h"
#include "PawnAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UPawnAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public :
	UPawnAnimInstance();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EPawnAnimType	m_PawnAnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	float				m_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	float				m_Angle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UPawnAnimState*		m_PawnAnimState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UPawnAnimCombo*		m_PawnAnimCombo;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "EDirection", AllowPrivateAccess = "true"));
	int32			m_Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	ECombinationType	m_CombinationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class APawnCharacter* m_PawnCharacter;

protected :
	int32			m_InputDirection;
	ECombinationType	m_InputCombinationType;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private :
	UFUNCTION()
	void AnimNotify_EnableCombo();
	
	UFUNCTION()
	void AnimNotify_DisableCombo();

	UFUNCTION()
	void AnimNotify_EnableCounter();

	UFUNCTION()
	void AnimNotify_DisableCounter();

	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_CastStart();

	UFUNCTION()
	void AnimNotify_CastEnd();

	UFUNCTION()
	void AnimNotify_DefenceStart();

	UFUNCTION()
	void AnimNotify_DefenceEnd();

protected :
	virtual void UpdatePawnType(EPawnAnimType BeforePawnAnimType, EPawnAnimType AfterPawnAnimType);
	virtual void UpdateSpecialAnim(UPawnAnimCombo* PawnAnimCombo, EComboType ComboType, int32 Direction, ECombinationType CombinationType);

public :
	virtual void SetPawnAnimType(EPawnAnimType PawnAnimType, bool EndAnimationStateOffset = false);
	virtual void SetReleasePawnAnimType(EPawnAnimType PawnAnimType);
	void SetAngle(float Angle);
	void SetSpeed(float Speed);
	void SetDirection(int32 Direction);
	void SetCombinationType(ECombinationType CombinationType);
	void SetEnableCounter(bool EnableCounter);

public :
	virtual EPawnAnimType GetPawnAnimType() const;
	float GetAngle() const;
	float GetSpeed() const;
	int32 GetDirection() const;
	ECombinationType GetCombinationType() const;

public :
	virtual void AddEndAnimationState(EPawnAnimType PawnAnimType);
	virtual void SetEndAnimationState(EPawnAnimType PawnAnimType, EPawnAnimType NextPawnAnimType = EPawnAnimType::Idle);
	virtual void ResetAnimationState(EPawnAnimType PawnAnimType);
	virtual void SetAnimationStateEndCount(EPawnAnimType PawnAnimType, int32 Count);
	EPawnAnimState GetAnimationState(EPawnAnimType PawnAnimType);
	virtual void StartAnimationState(EPawnAnimType PawnAnimType);
	virtual void StartAnimationState(EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType);
	virtual void StartAnimationState(EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType, class APawnCharacter* TargetCharacter);
};
