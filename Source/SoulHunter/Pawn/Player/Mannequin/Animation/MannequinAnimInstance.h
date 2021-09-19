// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../../../../GameInfo.h"
#include "../../Animation/PlayerAnimInstance.h"
#include "MannequinAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UMannequinAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()

protected :
	TArray<UAnimMontage*>	m_HeavyLancerAttackMontage;
	TArray<UAnimMontage*>	m_HeavyLancerStrongAttackMontage;
	UAnimMontage*			m_HeavyLancerDefenceMontage;
	bool					m_StartCombo;
	
public :
	UMannequinAnimInstance();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private :
	virtual void UpdatePawnType(EPawnAnimType BeforePawnAnimType, EPawnAnimType AfterPawnAnimType) override;
	virtual void UpdateSpecialAnim(UPawnAnimCombo* PawnAnimCombo, EComboType ComboType, int32 Direction, ECombinationType CombinationType) override;

protected :
};
