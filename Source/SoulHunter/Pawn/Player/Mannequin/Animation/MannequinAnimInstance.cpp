// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinAnimInstance.h"

//

UMannequinAnimInstance::UMannequinAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo01MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Pawn/Player/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerCombo1.MTMannequinHeavyLancerCombo1'"));

	if (Combo01MontageAsset.Succeeded())
		m_HeavyLancerComboMontage.Add(Combo01MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo02MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Pawn/Player/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerCombo2.MTMannequinHeavyLancerCombo2'"));

	if (Combo02MontageAsset.Succeeded())
		m_HeavyLancerComboMontage.Add(Combo02MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo03MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Pawn/Player/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerCombo3.MTMannequinHeavyLancerCombo3'"));

	if (Combo03MontageAsset.Succeeded())
		m_HeavyLancerComboMontage.Add(Combo03MontageAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo04MontageAsset(TEXT("AnimMontage'/Game/SoulHunter/Pawn/Player/Mannequin/Animation/HeavyLancer/MTMannequinHeavyLancerCombo4.MTMannequinHeavyLancerCombo4'"));

	if (Combo04MontageAsset.Succeeded())
		m_HeavyLancerComboMontage.Add(Combo04MontageAsset.Object);

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

void UMannequinAnimInstance::UpdateAnimCombo(UPawnAnimCombo* PawnAnimCombo, EComboType ComboType, EDirection Direction)
{
	if (EComboType::Attack == ComboType)
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
			PawnAnimCombo->SetAnimMontage(m_HeavyLancerComboMontage[Index], ComboCount);
		}
	}
	else if (EComboType::Defence == ComboType)
	{
		PrintViewport(1.f, FColor::Red, TEXT("UpdateAnimCOmbo Defence"));

		PawnAnimCombo->SetAnimMontage(m_HeavyLancerDefenceMontage);
	}
}