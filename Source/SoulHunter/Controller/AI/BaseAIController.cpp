// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "../../Character/BaseCharacter.h"

ABaseAIController::ABaseAIController()
{
	//m_eNPCAIControllerType = ENPCAIControllerType::Max;
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AIAsset(TEXT("BehaviorTree'/Game/SoulHunter/ActorController/AIController/BT/BTBase.BTBase'"));

	if (AIAsset.Succeeded())
		m_AITree = AIAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> AIDataAsset(TEXT("BlackboardData'/Game/SoulHunter/ActorController/AIController/BT/BBBase.BBBase'"));

	if (AIDataAsset.Succeeded())
		m_AIBlackBoard = AIDataAsset.Object;

	m_BBTraceRangeName = TEXT("TraceRange");
	m_BBTargetCharacterName = TEXT("TargetCharacter");

	m_AIControllerType = EAIControllerType::Base;

	ActorControllerType = static_cast<uint8>(EActorControllerType::BaseAI);
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	m_BaseCharacter = Cast<ABaseCharacter>(InPawn);

	if (false == IsValid(m_BaseCharacter))
	{
		LOG(TEXT("ABaseAIController::OnPossess Not found the Character"));
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

	LOG(TEXT("Update Behavior Tree Success"));
}

void ABaseAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

	SetBlackboardTraceRange(m_TraceRange);
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseAIController::SetBlackboardTraceRange(float TraceRange)
{
	Blackboard->SetValueAsFloat(m_BBTraceRangeName, TraceRange);
}

void ABaseAIController::SetBlackboardTargetCharacter(ABaseCharacter* BaseCharacter)
{
	Blackboard->SetValueAsObject(m_BBTargetCharacterName, BaseCharacter);
}

float ABaseAIController::GetBlackboardTraceRange() const
{
	return Blackboard->GetValueAsFloat(m_BBTraceRangeName);
}

ABaseCharacter* ABaseAIController::GetBlackboardTargetCharacter() const
{
	return Cast<ABaseCharacter>(Blackboard->GetValueAsObject(m_BBTargetCharacterName));
}

void ABaseAIController::StartAnimationState(EBaseAnimType BaseAnimType)
{
	m_BaseCharacter->StartAnimationState(BaseAnimType);
}

void ABaseAIController::StartAnimationState(EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType)
{
	m_BaseCharacter->StartAnimationState(BaseAnimType, Direction, CombinationType);
}

void ABaseAIController::StartAnimationState(EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType, class ABaseCharacter* TargetCharacter)
{
	m_BaseCharacter->StartAnimationState(BaseAnimType, Direction, CombinationType, TargetCharacter);
}

EBaseAnimState ABaseAIController::GetAnimationState(EBaseAnimType BaseAnimType) const
{
	return m_BaseCharacter->GetAnimationState(BaseAnimType);
}

void ABaseAIController::EndAnimationState(EBaseAnimType BaseAnimType)
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->SetEndAnimationState(BaseAnimType);

		return m_BaseCharacter->ResetAnimationState(BaseAnimType);
	}
	//m_NPCCharacter->SetEndAnimationState(BaseAnimType);
}

