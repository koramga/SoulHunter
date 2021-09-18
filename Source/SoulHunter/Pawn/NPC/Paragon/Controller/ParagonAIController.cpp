// Fill out your copyright notice in the Description page of Project Settings.


#include "ParagonAIController.h"
#include "../ParagonCharacter.h"

AParagonAIController::AParagonAIController()
{
	m_NPCAIControllerType = ENPCAIControllerType::Paragon;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AIAsset(TEXT("BehaviorTree'/Game/SoulHunter/Pawn/NPC/Paragon/Controller/BTParagon.BTParagon'"));

	if (AIAsset.Succeeded())
		m_AITree = AIAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> AIDataAsset(TEXT("BlackboardData'/Game/SoulHunter/Pawn/NPC/Paragon/Controller/BBParagon.BBParagon'"));

	if (AIDataAsset.Succeeded())
		m_AIBlackBoard = AIDataAsset.Object;
}

void AParagonAIController::OnPossess(APawn* InPawn)
{
	LOG(TEXT("AParagonAIController::OnPossess"));

	AParagonCharacter* ParagonCharacter = Cast<AParagonCharacter>(InPawn);

	if (nullptr == ParagonCharacter)
	{
		LOG(TEXT("AParagonAIController::OnPossess Not found the ParagonCharacter"));
		return;
	}

	if (false == UseBlackboard(m_AIBlackBoard, Blackboard))
	{
		LOG(TEXT("AParagonAIController::OnPossess UseBlackboard Failed.."));
		return;
	}

	if (false == RunBehaviorTree(m_AITree))
	{
		LOG(TEXT("AParagonAIController::OnPossess Runbehavior tree failed.."));
		return;
	}

	LOG(TEXT("RunBehaviorTree Success"));


	//AParagonTerraCharacter* pParagonTerraCharacter = nullptr;
	//
	//switch (eParagonCharacterType)
	//{
	//case EParagonCharacterType::Terra :
	//	pParagonTerraCharacter = Cast<AParagonTerraCharacter>(pParagonCharacter);
	//	break;
	//case EParagonCharacterType::Raven :
	//	break;
	//case EParagonCharacterType::Sparrow :
	//	break;
	//}
	//
	//if (nullptr != pParagonTerraCharacter)
	//{
	//	LOG(TEXT("Success cast from terra"));
	//}

	Super::OnPossess(InPawn);
}

void AParagonAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AParagonAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}