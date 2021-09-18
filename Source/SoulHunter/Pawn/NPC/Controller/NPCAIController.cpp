// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "../NPCCharacter.h"

ANPCAIController::ANPCAIController()
{
	//m_eNPCAIControllerType = ENPCAIControllerType::Max;
	PrimaryActorTick.bCanEverTick = true;

	m_BBTraceRangeName = TEXT("TraceRange");
	m_BBTargetPawnCharacterName = TEXT("TargetPawnCharacter");

	m_NPCAIControllerType = ENPCAIControllerType::Max;
}

void ANPCAIController::OnPossess(APawn* InPawn)
{
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

void ANPCAIController::SetBlackboardTraceRange(float TraceRange)
{
	Blackboard->SetValueAsFloat(m_BBTraceRangeName, TraceRange);
}

void ANPCAIController::SetBlackboardTargetPawnCharacter(class APawnCharacter* PawnCharacter)
{
	Blackboard->SetValueAsObject(m_BBTargetPawnCharacterName, PawnCharacter);
}

float ANPCAIController::GetBlackboardTraceRange() const
{
	return Blackboard->GetValueAsFloat(m_BBTraceRangeName);
}

class APawnCharacter* ANPCAIController::GetBlackboardTargetPawnCharacter() const
{
	return Cast<APawnCharacter>(Blackboard->GetValueAsObject(m_BBTargetPawnCharacterName));
}


void ANPCAIController::StartAnimationState(EPawnAnimType PawnAnimType)
{
	m_NPCCharacter->StartAnimationState(PawnAnimType);
}

void ANPCAIController::StartAnimationState(EPawnAnimType PawnAnimType, EDirection Direction, ECombinationType CombinationType)
{
	m_NPCCharacter->StartAnimationState(PawnAnimType, Direction, CombinationType);
}

void ANPCAIController::StartAnimationState(EPawnAnimType PawnAnimType, EDirection Direction, ECombinationType CombinationType, class APawnCharacter* TargetCharacter)
{
	m_NPCCharacter->StartAnimationState(PawnAnimType, Direction, CombinationType, TargetCharacter);
}

EPawnAnimState ANPCAIController::GetAnimationState(EPawnAnimType PawnAnimType) const
{
	return m_NPCCharacter->GetAnimationState(PawnAnimType);
}

void ANPCAIController::EndAnimationState(EPawnAnimType PawnAnimType)
{
	m_NPCCharacter->SetEndAnimationState(PawnAnimType);
}

void ANPCAIController::ResetAnimationState(EPawnAnimType PawnAnimType)
{
	m_NPCCharacter->ResetAnimationState(PawnAnimType);
}