// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseActor.h"
#include "MovementActor.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API AMovementActor : public ABaseActor
{
	GENERATED_BODY()
	
public :
	AMovementActor();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_Speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected :
	virtual void OnOverlapBeginFromBody(UPrimitiveComponent* OverlappedComp, const FHitResult& HitResult);
};
