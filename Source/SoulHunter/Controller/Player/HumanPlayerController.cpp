// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayerController.h"
#include "../../Character/Human/HumanCharacter.h"

AHumanPlayerController::AHumanPlayerController()
{
	ActorControllerType = static_cast<uint8>(EActorControllerType::HumanPlayer);
}

void AHumanPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AHumanPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	m_HumanCharacter = Cast<AHumanCharacter>(aPawn);

	if (IsValid(m_HumanCharacter))
	{
		m_HumanCharacter->SetHumanClassType(EHumanClassType::Spearman);
	}
}

void AHumanPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AHumanPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (IsValid(m_HumanCharacter))
	{
		
	}
}