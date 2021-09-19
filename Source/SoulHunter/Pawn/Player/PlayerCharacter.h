// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../PawnCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API APlayerCharacter : public APawnCharacter
{
	GENERATED_BODY()

public :
	APlayerCharacter();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	USpringArmComponent* m_Arm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class UPlayerAnimInstance* m_PlayerAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EToggleWalkAndRun	m_ToggleWalkAndRun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	bool m_DilationToggle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class UPlayerVR* m_PlayerVR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EPlayerCharacterType	m_PlayerCharacterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	bool m_DefenceOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	float m_DilationTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private :
	void __InputMoveForwardBack(float Scale);
	void __InputMoveLeftRight(float Scale);
	void __InputDirectionTypeKey(float Scale);
	void __InputCombinationTypeKey(float Scale);
	void __InputToggleWalkAndRun();
	void __InputToggleKey();
	void __InputDefenceKey();
	void __InputAttackKey();
	void __InputAvoidKey();
	void __InputRollKey();
	void __InputLockOnKey();

public :
	void AddArmPitch(float Value);
	void SetPlayerClassType(EPlayerClassType PlayerClassType);

public :
	virtual bool CanMove();
	virtual void UpdateMoveAnimation();

protected :
	virtual void NotifyAnimation(EAnimationNotifyType AnimationNotifyType, EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType) override;
	void WeaponActorTakeDamage(class ABaseActor* BaseActor, float Damage, float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
};