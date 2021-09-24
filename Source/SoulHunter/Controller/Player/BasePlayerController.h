// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class ABaseCharacter* m_BaseCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<UMatineeCameraShake>	m_CameraShake;

protected:
	// Called when the game starts or when sBaseed
	virtual void BeginPlay() override;

public:
	/**
	 * Processes player input (immediately after PlayerInput gets ticked) and calls UpdateRotation().
	 * PlayerTick is only called if the PlayerController has a PlayerInput object. Therefore, it will only be called for locally controlled PlayerControllers.
	 */
	virtual void PlayerTick(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

public:
	void CameraShake();

private:
	void __InputMoveForwardBack(float Scale);
	void __InputMoveLeftRight(float Scale);
	void __InputDirectionTypeKey(float Scale);
	void __InputCombinationTypeKey(float Scale);
	void __InputToggleWalkAndRun();
	void __InputToggleKey();
	void __InputDefenceKey();
	void __InputDefenceReleaseKey();
	void __InputAttackKey();
	void __InputAvoidKey();
	void __InputRollKey();
	void __InputLockOnKey();
	
};
