// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"
#include "Controller/NPCAIController.h"

ANPCCharacter::ANPCCharacter()
{
	m_NPCCharacterType = ENPCCharacterType::Max;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ANPCAIController::StaticClass();
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	ANPCAIController* AIController = GetController<ANPCAIController>();

	if (IsValid(AIController))
	{
		AIController->SetBlackboardTraceRange(1000.f);
	}
}

void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}