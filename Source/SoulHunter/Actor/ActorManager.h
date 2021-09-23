// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseActor.h"
#include "Item/weaponActor.h"
#include "UObject/NoExportTypes.h"
#include "ActorManager.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UActorManager : public UObject
{
	GENERATED_BODY()
	
public :
	UActorManager();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	TMap<FName, TSubclassOf<ABaseActor>>		m_mapActors;

public :
	void Init();

public :
	ABaseActor* CreateActor(const FName& Name, AActor* Owner) const;
	ABaseActor* CreateActor(const FName& Name, AActor* Owner, const FVector& Location, const FRotator& Rotator) const;
	ABaseActor* CreateActor(const FName& Name, AActor* Owner, const FVector& Location, const FRotator& Rotator, const FActorSpawnParameters& param) const;
};
