// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../HumanCharacter.h"
#include "Haena.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API AHaena : public AHumanCharacter
{
	GENERATED_BODY()

public:
	AHaena();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	USkeletalMeshComponent* m_Hair;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
