// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskTraceTarget.h"
#include "../../PawnCharacter.h"
#include "NPCAIController.h"
#include "../NPCCharacter.h"

UBTTaskTraceTarget::UBTTaskTraceTarget()
{
	NodeName = TEXT("TraceTargetTask");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskTraceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

void UBTTaskTraceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
		NPCAIController->StopMovement();
		NPCAIController->EndAnimationState(EPawnAnimType::Run);
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	
	EPawnAnimState PawnAnimState = NPCAIController->GetAnimationState(EPawnAnimType::Run);
	
	if (EPawnAnimState::None == PawnAnimState)
	{
		NPCAIController->StartAnimationState(EPawnAnimType::Run);
	}
	
	FVector vTargetPos = TargetCharacter->GetActorLocation();
	FVector vNPCPos = NPCCharacter->GetActorLocation();
	
	if (FMath::Abs<float>(vNPCPos.Z - vTargetPos.Z) <= 150.f)
	{
		vTargetPos.Z = vNPCPos.Z;
	}
	
	NPCAIController->MoveToLocation(vTargetPos, 0.f);	
	
	float fDistance = FVector::Distance(vTargetPos, vNPCPos);
	
	float fAttackRange = 100.f;//NPCAIController->GetBlackboardAttackRange();
	
	if (fDistance <= fAttackRange)
	{
		LOG(TEXT("End Animation State"));

		NPCAIController->EndAnimationState(EPawnAnimType::Run);
		NPCAIController->StopMovement();
		
		return FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		LOG(TEXT("Range : <%.2f>"), fDistance);
	}
}