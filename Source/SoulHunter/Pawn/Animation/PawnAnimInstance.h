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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EDirection			m_Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	ECombinationType	m_CombinationType;

protected :
	EDirection			m_InputDirection;
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

protected :
	virtual void UpdatePawnType(EPawnAnimType BeforePawnAnimType, EPawnAnimType AfterPawnAnimType);
	virtual void UpdateSpecialAnim(UPawnAnimCombo* PawnAnimCombo, EComboType ComboType, EDirection Direction, ECombinationType CombinationType);

public :
	virtual void SetPawnAnimType(EPawnAnimType PawnAnimType, bool EndAnimationStateOffset = false);
	void SetAngle(float Angle);
	void SetSpeed(float Speed);
	void SetDirection(EDirection Direction);
	void SetCombinationType(ECombinationType CombinationType);

public :
	virtual EPawnAnimType GetPawnAnimType() const;
	float GetAngle() const;
	float GetSpeed() const;
	EDirection GetDirection() const;
	ECombinationType GetCombinationType() const;

public :
	virtual void AddEndAnimationState(EPawnAnimType PawnAnimType);
	virtual void SetEndAnimationState(EPawnAnimType PawnAnimType, EPawnAnimType NextPawnAnimType = EPawnAnimType::Idle);
	virtual void ResetAnimationState(EPawnAnimType PawnAnimType);
	virtual void SetAnimationStateEndCount(EPawnAnimType PawnAnimType, int32 Count);
};
