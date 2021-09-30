// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskTraceTarget.h"
#include "../BaseAIController.h"
#include "../../../Character/BaseCharacter.h"

UBTTaskTraceTarget::UBTTaskTraceTarget()
{
	NodeName = TEXT("TraceTargetTask");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskTraceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

void UBTTaskTraceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
		BaseAIController->StopMovement();
		BaseAIController->EndAnimationState(EBaseAnimType::Run);
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	
	EBaseAnimState BaseAnimState = BaseAIController->GetAnimationState(EBaseAnimType::Run);
	
	if (EBaseAnimState::None == BaseAnimState)
	{
		BaseAIController->StartAnimationState(EBaseAnimType::Run);
	}
	
	FVector vTargetPos = TargetCharacter->GetActorLocation();
	FVector vNPCPos = BaseCharacter->GetActorLocation();
	
	if (FMath::Abs<float>(vNPCPos.Z - vTargetPos.Z) <= 150.f)
	{
		vTargetPos.Z = vNPCPos.Z;
	}
	
	BaseAIController->MoveToLocation(vTargetPos, 0.f);	
	
	float fDistance = FVector::Distance(vTargetPos, vNPCPos);
	
	float fAttackRange = 100.f;//NPCAIController->GetBlackboardAttackRange();
	
	if (fDistance <= fAttackRange)
	{
		LOG(TEXT("End Animation State"));

		BaseAIController->EndAnimationState(EBaseAnimType::Run);
		BaseAIController->StopMovement();
		
		return FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		LOG(TEXT("Range : <%.2f>"), fDistance);
	}
}