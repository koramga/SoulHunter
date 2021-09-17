// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinAnimInstance.h"

//

UMannequinAnimInstance::UMannequinAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack01MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Pawn/Player/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerCombo1.MTMannequinHeavyLancerCombo1'"));

	if (Attack01MontageAsset.Succeeded())
		m_HeavyLancerAttackMontage.Add(Attack01MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack02MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Pawn/Player/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerCombo2.MTMannequinHeavyLancerCombo2'"));

	if (Attack02MontageAsset.Succeeded())
		m_HeavyLancerAttackMontage.Add(Attack02MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack03MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Pawn/Player/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerCombo3.MTMannequinHeavyLancerCombo3'"));

	if (Attack03MontageAsset.Succeeded())
		m_HeavyLancerAttackMontage.Add(Attack03MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack04MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Pawn/Player/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerCombo4.MTMannequinHeavyLancerCombo4'"));

	if (Attack04MontageAsset.Succeeded())
		m_HeavyLancerAttackMontage.Add(Attack04MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> StrongAttack01MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Pawn/Player/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerDash.MTMannequinHeavyLancerDash'"));

	if (StrongAttack01MontageAsset.Succeeded())
		m_HeavyLancerStrongAttackMontage.Add(StrongAttack01MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DefenceMontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Pawn/Player/Mannequin/Animation/HeavyLancer/MTMannequinDefence.MTMannequinDefence'"));

	if (DefenceMontageAsset.Succeeded())
		m_HeavyLancerDefenceMontage = DefenceMontageAsset.Object;

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

void UMannequinAnimInstance::UpdatePawnType(EPawnAnimType BeforePawnAnimType, EPawnAnimType AfterPawnAnimType)
{
	Super::UpdatePawnType(BeforePawnAnimType, AfterPawnAnimType);
}

void UMannequinAnimInstance::UpdateSpecialAnim(UPawnAnimCombo* PawnAnimCombo, EComboType ComboType, EDirection Direction, ECombinationType CombinationType)
{
	if (EComboType::Attack == ComboType)
	{
		if(ECombinationType::None == CombinationType)
		{
			int Index = -1;
			int ComboCount = 4;

			switch (Direction)
			{
			case EDirection::Left:
				Index = 3;
				break;
			case EDirection::Right:
				Index = 2;
				break;
			case EDirection::Forward:
				ComboCount = 3;
				Index = 0;
				break;
			case EDirection::Back:
				Index = 1;
				break;
			}

			if (Index >= 0)
			{
				PawnAnimCombo->SetAnimMontage(m_HeavyLancerAttackMontage[Index], ComboCount);
			}
		}
		else if (ECombinationType::Strong == CombinationType)
		{
			PawnAnimCombo->SetAnimMontage(m_HeavyLancerStrongAttackMontage[0]);
		}
	}
	else if (EComboType::Defence == ComboType)
	{
		PawnAnimCombo->SetAnimMontage(m_HeavyLancerDefenceMontage);
	}
}