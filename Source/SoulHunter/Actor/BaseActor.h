// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

DECLARE_DELEGATE_OneParam(FItemEndPlayCallback, class ABaseActor*)
DECLARE_DELEGATE_TwoParams(FItemHitCallback, class ABaseActor*, const FHitResult&)
DECLARE_DELEGATE_TwoParams(FItemOverlapBeginCallback, class ABaseActor*, const FHitResult&)
DECLARE_DELEGATE_TwoParams(FItemOverlapEndCallback, class ABaseActor*, class AActor*)

UCLASS()
class SOULHUNTER_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* m_Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_Body;

protected:
	FItemHitCallback			m_HitCallback;
	FItemOverlapBeginCallback	m_OverlapBeginCallback;
	FItemOverlapEndCallback		m_OverlapEndCallback;
	FItemEndPlayCallback		m_EndPlayItemCallback;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp
		, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor
		, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor
		, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected :
	virtual void OnOverlapBeginFromBody(UPrimitiveComponent* OverlappedComp, const FHitResult& HitResult);
	virtual void OnOverlapEndFromBody(class UPrimitiveComponent* OverlappedComp, AActor* OverlapEndActor);

public :
	void AddIgnoreActorWhenMoving(AActor* pActor);
	void ClearIgnoreActorWhenMoving();

public :
	FVector GetBodyExtent() const;
};
