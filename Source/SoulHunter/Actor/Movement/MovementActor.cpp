// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementActor.h"

AMovementActor::AMovementActor()
{

}

void AMovementActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMovementActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();

	SetActorLocation(Location + GetActorForwardVector() * m_Speed * DeltaTime);
}


void AMovementActor::OnOverlapBeginFromBody(UPrimitiveComponent* OverlappedComp, const FHitResult& HitResult)
{
	AActor* HitResultActor = HitResult.Actor.Get();

	if (IsValid(HitResultActor)
		&& HitResultActor != this)
	{
		FDamageEvent DamageEvent;

		LOG(TEXT("TakeDamage!! <%s>"), *HitResultActor->GetName());

		HitResultActor->TakeDamage(1.f, DamageEvent, nullptr, this);

		Destroy();
	}
}