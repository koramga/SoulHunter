// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "../NPCCharacter.h"

ANPCAIController::ANPCAIController()
{
	//m_eNPCAIControllerType = ENPCAIControllerType::Max;
	PrimaryActorTick.bCanEverTick = true;

	m_NPCAIControllerType = ENPCAIControllerType::Max;
}

void ANPCAIController::OnPossess(APawn* InPawn)
{
	//LOG(TEXT("ANPCAIController::OnPossess"));
	Super::OnPossess(InPawn);

	m_NPCCharacter = Cast<ANPCCharacter>(InPawn);
}

void ANPCAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ANPCAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}