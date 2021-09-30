// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskAttackTarget.h"
#include "../BaseAIController.h"
#include "../../../Character/BaseCharacter.h"

UBTTaskAttackTarget::UBTTaskAttackTarget()
{
	NodeName = TEXT("AttackTargetTask");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskAttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseAIController* BaseAIController = Cast<ABaseAIController>(OwnerComp.GetOwner());

	if (nullptr == BaseAIController)
	{
		return EBTNodeResult::Failed;
	}

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(BaseAIController->GetPawn());

	if (nullptr == BaseCharacter)
	{
		return EBTNodeResult::Failed;
	}

	if (BaseCharacter->IsDeath())
	{
		return EBTNodeResult::Failed;
	}

	ABaseCharacter* TargetCharacter = BaseAIController->GetBlackboardTargetCharacter();

	if (nullptr == TargetCharacter)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskAttackTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ABaseAIController* BaseAIController = Cast<ABaseAIController>(OwnerComp.GetOwner());

	if (nullptr == BaseAIController)
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(BaseAIController->GetPawn());

	if (nullptr == BaseCharacter)
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (BaseCharacter->IsDeath())
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	ABaseCharacter* TargetCharacter = BaseAIController->GetBlackboardTargetCharacter();

	if (false == IsValid(TargetCharacter))
	{
		BaseAIController->EndAnimationState(EBaseAnimType::Attack);
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	EBaseAnimState BaseAnimState = BaseAIController->GetAnimationState(EBaseAnimType::Attack);

	if (EBaseAnimState::None == BaseAnimState)
	{
		BaseAIController->StartAnimationState(EBaseAnimType::Attack, DIRECTION_FORWARD, ECombinationType::None, TargetCharacter);
	}
	else if(EBaseAnimState::End == BaseAnimState)
	{
		LOG(TEXT("AttackTarget End Success!!"));

		BaseAIController->EndAnimationState(EBaseAnimType::Attack);
		return FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}