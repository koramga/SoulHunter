// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Animation/HumanAnimInstance.h"
#include "MannequinAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UMannequinAnimInstance : public UHumanAnimInstance
{
	GENERATED_BODY()

protected :
	TArray<UAnimMontage*>	m_HeavyLancerAttackMontage;
	TArray<UAnimMontage*>	m_HeavyLancerStrongAttackMontage;
	UAnimMontage*			m_HeavyLancerDefenceMontage;


	TArray<UAnimMontage*>	m_SpearmanAttackMontage;
	TArray<UAnimMontage*>	m_SpearmanStrongAttackMontage;
	UAnimMontage*			m_SpearmanDefenceMontage;

	bool					m_StartCombo;
	
public :
	UMannequinAnimInstance();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private :
	virtual void UpdateBaseType(EBaseAnimType BeforeBaseAnimType, EBaseAnimType AfterBaseAnimType) override;
	virtual void UpdateSpecialAnim(UBaseAnimCombo* BaseAnimCombo, EComboType ComboType, int32 Direction, ECombinationType CombinationType) override;

protected :
};
