// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class SOULHUNTER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	USpringArmComponent* m_Arm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class UBaseAnimInstance* m_BaseAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	float m_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	float m_Angle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	int32 m_AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	int32 m_ComboType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	ABaseCharacter* m_LockOnBaseCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	bool					m_LockOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EToggleWalkAndRun		m_ToggleWalkAndRun;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	ECharacterType			m_CharacterType;

	//int32
protected:
	// Called when the game starts or when sBaseed
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)	override;
	
public:
	virtual void AddEndAnimationState(EBaseAnimType BaseCharacterAnimType);
	virtual void SetEndAnimationState(EBaseAnimType BaseCharacterAnimType);
	virtual void ResetAnimationState(EBaseAnimType BaseCharacterAnimType);
	virtual void SetAnimationStateEndCount(EBaseAnimType BaseCharacterAnimType, int32 Count);
	EBaseAnimState GetAnimationState(EBaseAnimType BaseAnimType) const;
	virtual void StartAnimationState(EBaseAnimType BaseAnimType);
	virtual void StartAnimationState(EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType);
	virtual void StartAnimationState(EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType, class ABaseCharacter* TargetCharacter);
	virtual void NotifyAnimation(EAnimationNotifyType AnimationNotifyType, EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType);

public:
	EBaseAnimType GetBaseAnimType() const;
	virtual bool IsDeath() const;
	virtual bool IsLockOn() const;
	virtual bool CanMove() const;
	float GetAngle() const;
	float GetSpeed() const;
	EToggleWalkAndRun GetToggleWalkAndRun() const;
	bool IsMoveAnimation() const;
	bool IsIdleAnimation() const;
	ECharacterType GetCharacterType() const;

public :
	void SetBaseAnimType(EBaseAnimType BaseAnimType);
	void SetEndBaseAnimType();
	void SetDirection(int32 Direction);
	void SetCombinationType(ECombinationType CombinationType);
	void SetToggleWalkAndRun();
	void SetTestToggle();
	void AddArmPitch(float Value);
};
