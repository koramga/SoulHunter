// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Controller/NPCAIController.h"
#include "ParagonAIController.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API AParagonAIController : public ANPCAIController
{
	GENERATED_BODY()

public :
	AParagonAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void Tick(float DeltaTime) override;
};
