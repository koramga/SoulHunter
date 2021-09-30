// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskAttackTarget.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UBTTaskAttackTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskAttackTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	
};
