// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "AIController.h"
#include "NPCAIController.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
	
public :
	ANPCAIController();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UBehaviorTree* m_AITree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UBlackboardData* m_AIBlackBoard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	ENPCAIControllerType m_NPCAIControllerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class ANPCCharacter* m_NPCCharacter;

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FName		m_BBTraceRangeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FName		m_BBTargetPawnCharacterName;

public :
	void SetBlackboardTraceRange(float TraceRange);
	void SetBlackboardTargetPawnCharacter(class APawnCharacter* PawnCharacter);

public :
	float GetBlackboardTraceRange() const;
	class APawnCharacter* GetBlackboardTargetPawnCharacter() const;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void Tick(float DeltaTime) override;

};
