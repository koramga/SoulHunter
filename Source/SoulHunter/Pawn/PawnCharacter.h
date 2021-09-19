// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "PawnCharacter.generated.h"

UCLASS()
class SOULHUNTER_API APawnCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APawnCharacter();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class UPawnAnimInstance* m_PawnAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	float m_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	float m_Angle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	int32 m_AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	int32 m_ComboType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	APawnCharacter* m_LookAtPawnCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	bool					m_LookAtMode;

	//int32
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public :
	EPawnAnimType GetPawnAnimType() const;

public :
	virtual void AddEndAnimationState(EPawnAnimType PawnCharacterAnimType);
	virtual void SetEndAnimationState(EPawnAnimType PawnCharacterAnimType);
	virtual void ResetAnimationState(EPawnAnimType PawnCharacterAnimType);
	virtual void SetAnimationStateEndCount(EPawnAnimType PawnCharacterAnimType, int32 Count);
	EPawnAnimState GetAnimationState(EPawnAnimType PawnAnimType) const;
	virtual void StartAnimationState(EPawnAnimType PawnAnimType);
	virtual void StartAnimationState(EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType);
	virtual void StartAnimationState(EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType, class APawnCharacter* TargetCharacter);

public :
	virtual bool IsDeath();
};