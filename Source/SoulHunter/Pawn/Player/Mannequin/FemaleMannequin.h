// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerCharacter.h"
#include "FemaleMannequin.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API AFemaleMannequin : public APlayerCharacter
{
	GENERATED_BODY()

public:
	AFemaleMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
