// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

DECLARE_DELEGATE_OneParam(FBaseActorEndPlayCallback, class ABaseActor*)
DECLARE_DELEGATE_TwoParams(FBaseActorHitCallback, class ABaseActor*, const FHitResult&)
DECLARE_DELEGATE_TwoParams(FBaseActorOverlapBeginCallback, class ABaseActor*, const FHitResult&)
DECLARE_DELEGATE_TwoParams(FBaseActorOverlapEndCallback, class ABaseActor*, class AActor*)
DECLARE_DELEGATE_SixParams(FBaseActorTakeDamageCallback, class ABaseActor*, float, float, struct FDamageEvent const&, class AController*, AActor*)

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActorType		m_ActorType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName			m_BodyCollisionProfileName;

protected:
	FBaseActorHitCallback			m_HitCallback;
	FBaseActorOverlapBeginCallback	m_OverlapBeginCallback;
	FBaseActorOverlapEndCallback	m_OverlapEndCallback;
	FBaseActorEndPlayCallback		m_EndPlayCallback;
	FBaseActorTakeDamageCallback	m_TakeDamageCallback;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)	override;

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

public:
	template <typename T>
	void SetHitCallback(T* pObj, void (T::* pFunc)(ABaseActor*, const FHitResult&))
	{
		m_HitCallback.BindUObject(pObj, pFunc);
	}

	template <typename T>
	void SetEndPlayCallback(T* pObj, void (T::* pFunc)(ABaseActor*))
	{
		m_EndPlayCallback.BindUObject(pObj, pFunc);
	}

	template <typename T>
	void SetOverlapBeginCallback(T* pObj, void (T::* pFunc)(ABaseActor*, const FHitResult&))
	{
		m_OverlapBeginCallback.BindUObject(pObj, pFunc);
	}

	template <typename T>
	void SetOverlapEndCallback(T* pObj, void (T::* pFunc)(ABaseActor*, const AActor*))
	{
		m_OverlapEndCallback.BindUObject(pObj, pFunc);
	}

	template <typename T>
	void SetTakeDamageCallback(T* pObj, void (T::* pFunc)(class ABaseActor*, float, float, struct FDamageEvent const&, class AController*, AActor*))
	{
		m_TakeDamageCallback.BindUObject(pObj, pFunc);
	}

protected :
	virtual void OnOverlapBeginFromBody(UPrimitiveComponent* OverlappedComp, const FHitResult& HitResult);
	virtual void OnOverlapEndFromBody(class UPrimitiveComponent* OverlappedComp, AActor* OverlapEndActor);

public :
	void AddIgnoreActorWhenMoving(AActor* pActor);
	void ClearIgnoreActorWhenMoving();

public :
	void SetEnableCollision(bool Enable);

public :
	FVector GetBodyExtent() const;
	EActorType GetActorType() const;
	bool IsEnableCollision() const;
};
