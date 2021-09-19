// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskAttackTarget.h"
#include "../../PawnCharacter.h"
#include "NPCAIController.h"
#include "../NPCCharacter.h"

UBTTaskAttackTarget::UBTTaskAttackTarget()
{
	NodeName = TEXT("AttackTargetTask");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskAttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	ANPCAIController* NPCAIController = Cast<ANPCAIController>(OwnerComp.GetOwner());

	if (nullptr == NPCAIController)
	{
		return EBTNodeResult::Failed;
	}

	ANPCCharacter* NPCCharacter = Cast<ANPCCharacter>(NPCAIController->GetPawn());

	if (nullptr == NPCCharacter)
	{
		return EBTNodeResult::Failed;
	}

	if (NPCCharacter->IsDeath())
	{
		return EBTNodeResult::Failed;
	}

	APawnCharacter* PawnCharacter = NPCAIController->GetBlackboardTargetPawnCharacter();

	if (nullptr == PawnCharacter)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskAttackTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ANPCAIController* NPCAIController = Cast<ANPCAIController>(OwnerComp.GetOwner());

	if (nullptr == NPCAIController)
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	ANPCCharacter* NPCCharacter = Cast<ANPCCharacter>(NPCAIController->GetPawn());

	if (nullptr == NPCCharacter)
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (NPCCharacter->IsDeath())
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	APawnCharacter* TargetCharacter = NPCAIController->GetBlackboardTargetPawnCharacter();

	if (false == IsValid(TargetCharacter))
	{
		NPCAIController->EndAnimationState(EPawnAnimType::Attack);
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	EPawnAnimState PawnAnimState = NPCAIController->GetAnimationState(EPawnAnimType::Attack);

	if (EPawnAnimState::None == PawnAnimState)
	{
		NPCAIController->StartAnimationState(EPawnAnimType::Attack, DIRECTION_FORWARD, ECombinationType::None, TargetCharacter);
	}
	else if(EPawnAnimState::End == PawnAnimState)
	{
		LOG(TEXT("AttackTarget End Success!!"));

		NPCAIController->EndAnimationState(EPawnAnimType::Attack);
		return FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}