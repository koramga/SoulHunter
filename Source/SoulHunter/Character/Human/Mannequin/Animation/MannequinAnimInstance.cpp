// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinAnimInstance.h"

//

UMannequinAnimInstance::UMannequinAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack01MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Character/Human/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerCombo1.MTMannequinHeavyLancerCombo1'"));

	if (Attack01MontageAsset.Succeeded())
		m_HeavyLancerAttackMontage.Add(Attack01MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack02MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Character/Human/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerCombo2.MTMannequinHeavyLancerCombo2'"));

	if (Attack02MontageAsset.Succeeded())
		m_HeavyLancerAttackMontage.Add(Attack02MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack03MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Character/Human/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerCombo3.MTMannequinHeavyLancerCombo3'"));

	if (Attack03MontageAsset.Succeeded())
		m_HeavyLancerAttackMontage.Add(Attack03MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack04MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Character/Human/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerCombo4.MTMannequinHeavyLancerCombo4'"));

	if (Attack04MontageAsset.Succeeded())
		m_HeavyLancerAttackMontage.Add(Attack04MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> StrongAttack01MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Character/Human/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerDash.MTMannequinHeavyLancerDash'"));

	if (StrongAttack01MontageAsset.Succeeded())
		m_HeavyLancerStrongAttackMontage.Add(StrongAttack01MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DefenceMontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Character/Human/Mannequin/Animation/HeavyLancer/MTMannequinDefence.MTMannequinDefence'"));

	if (DefenceMontageAsset.Succeeded())
		m_HeavyLancerDefenceMontage = DefenceMontageAsset.Object;




	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpearmanAttack01MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Character/Human/Mannequin/Animation/Spearman/MTMannequinSpearmanAttack01.MTMannequinSpearmanAttack01'"));

	if (SpearmanAttack01MontageAsset.Succeeded())
		m_SpearmanAttackMontage.Add(SpearmanAttack01MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpearmanAttack02MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Character/Human/Mannequin/Animation/Spearman/MTMannequinSpearmanAttack02.MTMannequinSpearmanAttack02'"));

	if (SpearmanAttack02MontageAsset.Succeeded())
		m_SpearmanAttackMontage.Add(SpearmanAttack02MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpearmanAttack03MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Character/Human/Mannequin/Animation/Spearman/MTMannequinSpearmanAttack03.MTMannequinSpearmanAttack03'"));

	if (SpearmanAttack03MontageAsset.Succeeded())
		m_SpearmanAttackMontage.Add(SpearmanAttack03MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpearmanAttack04MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Character/Human/Mannequin/Animation/Spearman/MTMannequinSpearmanAttack04.MTMannequinSpearmanAttack04'"));

	if (SpearmanAttack04MontageAsset.Succeeded())
		m_SpearmanAttackMontage.Add(SpearmanAttack04MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpearmanStrongAttack01MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Character/Human/Mannequin/Animation/Spearman/MTMannequinSpearmanStrongAttack01.MTMannequinSpearmanStrongAttack01'"));

	if (SpearmanStrongAttack01MontageAsset.Succeeded())
		m_SpearmanStrongAttackMontage.Add(SpearmanStrongAttack01MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpearmanDefenceMontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Character/Human/Mannequin/Animation/Spearman/MTMannequinSpearmanDefence.MTMannequinSpearmanDefence'"));

	if (SpearmanDefenceMontageAsset.Succeeded())
		m_SpearmanDefenceMontage = SpearmanDefenceMontageAsset.Object;

	m_StartCombo = false;
}

void UMannequinAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMannequinAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMannequinAnimInstance::UpdateBaseType(EBaseAnimType BeforeBaseAnimType, EBaseAnimType AfterBaseAnimType)
{
	Super::UpdateBaseType(BeforeBaseAnimType, AfterBaseAnimType);
}

void UMannequinAnimInstance::UpdateSpecialAnim(UBaseAnimCombo* BaseAnimCombo, EComboType ComboType, int32 Direction, ECombinationType CombinationType)
{
	if (EHumanClassType::HeavyLancer == m_HumanClassType)
	{
		if (EComboType::Attack == ComboType)
		{
			if (ECombinationType::None == CombinationType)
			{
				int Index = -1;

				if ((Direction & DIRECTION_FORWARD) > 0)
				{
					Index = 0;
				}
				else if ((Direction & DIRECTION_BACK) > 0)
				{
					Index = 1;
				}
				else if ((Direction & DIRECTION_LEFT) > 0)
				{
					Index = 3;
				}
				else if ((Direction & DIRECTION_RIGHT) > 0)
				{
					Index = 2;
				}

				if (Index >= 0)
				{
					BaseAnimCombo->SetAnimMontage(m_HeavyLancerAttackMontage[Index]);
				}
			}
			else if (ECombinationType::Strong == CombinationType)
			{
				BaseAnimCombo->SetAnimMontage(m_HeavyLancerStrongAttackMontage[0]);
			}
		}
		else if (EComboType::Defence == ComboType)
		{
			BaseAnimCombo->SetAnimMontage(m_HeavyLancerDefenceMontage, EComboType::Paring);
		}
	}
	else if (EHumanClassType::Spearman == m_HumanClassType)
	{
		if (EComboType::Attack == ComboType)
		{
			if (ECombinationType::None == CombinationType)
			{
				int Index = -1;

				if ((Direction & DIRECTION_FORWARD) > 0)
				{
					Index = 0;
				}
				else if ((Direction & DIRECTION_BACK) > 0)
				{
					Index = 1;
				}
				else if ((Direction & DIRECTION_LEFT) > 0)
				{
					Index = 3;
				}
				else if ((Direction & DIRECTION_RIGHT) > 0)
				{
					Index = 2;
				}

				if (Index >= 0)
				{
					BaseAnimCombo->SetAnimMontage(m_SpearmanAttackMontage[Index]);
				}
			}
			else if (ECombinationType::Strong == CombinationType)
			{
				BaseAnimCombo->SetAnimMontage(m_SpearmanStrongAttackMontage[0]);
			}
		}
		else if (EComboType::Defence == ComboType)
		{
			BaseAnimCombo->SetAnimMontage(m_SpearmanDefenceMontage, EComboType::Defence);
		}
	}
}