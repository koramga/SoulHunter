// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePlayerController.h"
#include "HumanPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API AHumanPlayerController : public ABasePlayerController
{
	GENERATED_BODY()

public :
	AHumanPlayerController();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class AHumanCharacter* m_HumanCharacter;

protected:
	// Called when the game starts or when sBaseed
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

public:
	/**
	 * Processes player input (immediately after PlayerInput gets ticked) and calls UpdateRotation().
	 * PlayerTick is only called if the PlayerController has a PlayerInput object. Therefore, it will only be called for locally controlled PlayerControllers.
	 */
	virtual void PlayerTick(float DeltaTime);
};
