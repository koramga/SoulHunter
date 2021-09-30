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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UBehaviorTree* m_AITree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UBlackboardData* m_AIBlackBoard;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EAIControllerType m_AIControllerType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class ABaseCharacter* m_BaseCharacter;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FName		m_BBTraceRangeName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FName		m_BBTargetCharacterName;

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	float		m_TraceRange;

public:
	void SetBlackboardTraceRange(float TraceRange);
	void SetBlackboardTargetCharacter(class ABaseCharacter* BaseCharacter);

public:
	float GetBlackboardTraceRange() const;
	class ABaseCharacter* GetBlackboardTargetCharacter() const;

public:
	virtual void StartAnimationState(EBaseAnimType BaseAnimType);
	virtual void StartAnimationState(EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType);
	virtual void StartAnimationState(EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType, class ABaseCharacter* TargetCharacter);
	EBaseAnimState GetAnimationState(EBaseAnimType BaseAnimType) const;
	virtual void EndAnimationState(EBaseAnimType BaseAnimType);
	//virtual void ResetAnimationState(EBaseAnimType BaseAnimType);

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

protected:
	// Called when the game starts or when sBaseed
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
};
