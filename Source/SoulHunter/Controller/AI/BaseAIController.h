// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public :
	ABaseAIController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UBehaviorTree* m_AITree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UBlackboardData* m_AIBlackBoard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EAIControllerType m_AIControllerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class APawnCharacter* m_PawnCharacter;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FName		m_BBTraceRangeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FName		m_BBTargetPawnCharacterName;

public:
	void SetBlackboardTraceRange(float TraceRange);
	void SetBlackboardTargetPawnCharacter(class APawnCharacter* PawnCharacter);

public:
	float GetBlackboardTraceRange() const;
	class APawnCharacter* GetBlackboardTargetPawnCharacter() const;

public:
	virtual void StartAnimationState(EPawnAnimType PawnAnimType);
	virtual void StartAnimationState(EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType);
	virtual void StartAnimationState(EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType, class APawnCharacter* TargetCharacter);
	EPawnAnimState GetAnimationState(EPawnAnimType PawnAnimType) const;
	virtual void EndAnimationState(EPawnAnimType PawnAnimType);
	//virtual void ResetAnimationState(EPawnAnimType PawnAnimType);

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void Tick(float DeltaTime) override;
	
};
