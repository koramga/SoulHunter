// Fill out your copyright notice in the Description page of Project Settings.


#include "ParagonCharacter.h"
#include "Controller/ParagonAIController.h"

AParagonCharacter::AParagonCharacter()
{
	m_NPCCharacterType = ENPCCharacterType::Paragon;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AParagonAIController::StaticClass();
}