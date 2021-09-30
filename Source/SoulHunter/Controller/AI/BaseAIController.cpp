// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "../../Pawn/PawnCharacter.h"

ABaseAIController::ABaseAIController()
{
	//m_eNPCAIControllerType = ENPCAIControllerType::Max;
	PrimaryActorTick.bCanEverTick = true;

	m_BBTraceRangeName = TEXT("TraceRange");
	m_BBTargetPawnCharacterName = TEXT("TargetPawnCharacter");

	m_AIControllerType = EAIControllerType::Max;

	ActorControllerType = static_cast<uint8>(EActorControllerType::BaseAI);
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	m_PawnCharacter = Cast<APawnCharacter>(InPawn);
}

void ABaseAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseAIController::SetBlackboardTraceRange(float TraceRange)
{
	Blackboard->SetValueAsFloat(m_BBTraceRangeName, TraceRange);
}

void ABaseAIController::SetBlackboardTargetPawnCharacter(class APawnCharacter* PawnCharacter)
{
	Blackboard->SetValueAsObject(m_BBTargetPawnCharacterName, PawnCharacter);
}

float ABaseAIController::GetBlackboardTraceRange() const
{
	return Blackboard->GetValueAsFloat(m_BBTraceRangeName);
}

class APawnCharacter* ABaseAIController::GetBlackboardTargetPawnCharacter() const
{
	return Cast<APawnCharacter>(Blackboard->GetValueAsObject(m_BBTargetPawnCharacterName));
}


void ABaseAIController::StartAnimationState(EPawnAnimType PawnAnimType)
{
	m_PawnCharacter->StartAnimationState(PawnAnimType);
}

void ABaseAIController::StartAnimationState(EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType)
{
	m_PawnCharacter->StartAnimationState(PawnAnimType, Direction, CombinationType);
}

void ABaseAIController::StartAnimationState(EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType, class APawnCharacter* TargetCharacter)
{
	m_PawnCharacter->StartAnimationState(PawnAnimType, Direction, CombinationType, TargetCharacter);
}

EPawnAnimState ABaseAIController::GetAnimationState(EPawnAnimType PawnAnimType) const
{
	return m_PawnCharacter->GetAnimationState(PawnAnimType);
}

void ABaseAIController::EndAnimationState(EPawnAnimType PawnAnimType)
{
	if (IsValid(m_PawnCharacter))
	{
		m_PawnCharacter->SetEndAnimationState(PawnAnimType);

		return m_PawnCharacter->ResetAnimationState(PawnAnimType);
	}
	//m_NPCCharacter->SetEndAnimationState(PawnAnimType);
}

