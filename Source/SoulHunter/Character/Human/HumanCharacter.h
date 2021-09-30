// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseCharacter.h"
#include "HumanCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API AHumanCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public :
	AHumanCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class UHumanAnimInstance* m_HumanAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	bool m_DilationToggle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class UPlayerVR* m_PlayerVR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EHumanClassType	m_HumanClassType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	bool m_DefenceOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	float m_DilationTime;

	//int32
protected:
	// Called when the game starts or when sBaseed
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected :
	void WeaponActorTakeDamage(class ABaseActor* BaseActor, float Damage, float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	void SetHumanClassType(EHumanClassType PlayerClassType);
	
};
