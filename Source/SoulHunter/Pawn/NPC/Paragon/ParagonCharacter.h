// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../NPCCharacter.h"
#include "ParagonCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API AParagonCharacter : public ANPCCharacter
{
	GENERATED_BODY()
	
public :
	AParagonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
