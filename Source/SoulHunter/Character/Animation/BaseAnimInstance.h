// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BaseAnimState.h"
#include "BaseAnimCombo.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public :
	UBaseAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EBaseAnimType	m_BaseAnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	float				m_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	float				m_Angle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UBaseAnimState* m_BaseAnimState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UBaseAnimCombo* m_BaseAnimCombo;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "EDirection", AllowPrivateAccess = "true"));
	int32			m_Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	ECombinationType	m_CombinationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class ABaseCharacter* m_BaseCharacter;

protected:
	int32			m_InputDirection;
	ECombinationType	m_InputCombinationType;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
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

	UFUNCTION()
		void AnimNotify_LHandStart();

	UFUNCTION()
		void AnimNotify_LHandEnd();

	UFUNCTION()
		void AnimNotify_RHandStart();

	UFUNCTION()
		void AnimNotify_RHandEnd();

	UFUNCTION()
		void AnimNotify_LFootStart();

	UFUNCTION()
		void AnimNotify_LFootEnd();

	UFUNCTION()
		void AnimNotify_RFootStart();

	UFUNCTION()
		void AnimNotify_RFootEnd();

protected:
	virtual void UpdateBaseType(EBaseAnimType BeforeBaseAnimType, EBaseAnimType AfterBaseAnimType);
	virtual void UpdateSpecialAnim(UBaseAnimCombo* BaseAnimCombo, EComboType ComboType, int32 Direction, ECombinationType CombinationType);

public:
	virtual void SetBaseAnimType(EBaseAnimType BaseAnimType, bool EndAnimationStateOffset = false);
	virtual void SetEndBaseAnimType();
	void SetAngle(float Angle);
	void SetSpeed(float Speed);
	void SetDirection(int32 Direction);
	void SetCombinationType(ECombinationType CombinationType);
	void SetEnableCounter(bool EnableCounter);

public:
	virtual EBaseAnimType GetBaseAnimType() const;
	float GetAngle() const;
	float GetSpeed() const;
	int32 GetDirection() const;
	ECombinationType GetCombinationType() const;
	bool IsEnableCounter() const;

public:
	virtual void AddEndAnimationState(EBaseAnimType BaseAnimType);
	virtual void SetEndAnimationState(EBaseAnimType BaseAnimType, EBaseAnimType NextBaseAnimType = EBaseAnimType::Idle);
	virtual void ResetAnimationState(EBaseAnimType BaseAnimType);
	virtual void SetAnimationStateEndCount(EBaseAnimType BaseAnimType, int32 Count);
	EBaseAnimState GetAnimationState(EBaseAnimType BaseAnimType);
	virtual void StartAnimationState(EBaseAnimType BaseAnimType);
	virtual void StartAnimationState(EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType);
	virtual void StartAnimationState(EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType, class ABaseCharacter* TargetCharacter);
	
};
