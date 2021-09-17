// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnAnimCombo.h"
#include "PawnAnimInstance.h"

UPawnAnimCombo::UPawnAnimCombo()
{
	m_EnableUpdateMontage = false;
}

FName UPawnAnimCombo::GetComboStartName(int32 ComboIndex)
{
	return FName(*FString::Printf(TEXT("Combo%02dStart"), ComboIndex));
}

FName UPawnAnimCombo::GetComboEndeName(int32 ComboIndex)
{
	return FName(*FString::Printf(TEXT("Combo%02dEnd"), ComboIndex));
}

void UPawnAnimCombo::SetAnimMontage(UAnimMontage* AnimMontage, int32 ComboCount)
{
	m_ComboMontage = AnimMontage;
	m_ComboCount = ComboCount;
	m_ComboIndex = 1;
	m_EnableUpdateMontage = false;
	m_ComboType = EComboType::Attack;
}

void UPawnAnimCombo::SetAnimMontage(UAnimMontage* AnimMontage)
{
	m_ComboMontage = AnimMontage;
	m_EnableUpdateMontage = false;
	m_ComboType = EComboType::Defence;
}

void UPawnAnimCombo::StartAnimMontage(UAnimInstance* AnimInstance)
{
	if (IsValid(m_ComboMontage))
	{
		AnimInstance->Montage_Play(m_ComboMontage);

		if (EComboType::Attack == m_ComboType)
		{
			AnimInstance->Montage_SetNextSection(UPawnAnimCombo::GetComboStartName(m_ComboIndex), UPawnAnimCombo::GetComboEndeName(m_ComboIndex));
		}
		else if (EComboType::Defence == m_ComboType)
		{
			AnimInstance->Montage_SetNextSection(TEXT("Start"), TEXT("End"));
			//카운터 성공하면 아래와같이 진행한다.
			//AnimInstance->Montage_SetNextSection(TEXT("Start"), TEXT("Counter"));
		}
	}
}

void UPawnAnimCombo::UpdateAnimMontage(UAnimInstance* AnimInstance)
{
	if (IsValid(m_ComboMontage))
	{
		if (EComboType::Attack == m_ComboType)
		{
			m_ComboIndex++;
			AnimInstance->Montage_SetNextSection(UPawnAnimCombo::GetComboStartName(m_ComboIndex - 1), UPawnAnimCombo::GetComboStartName(m_ComboIndex));
			AnimInstance->Montage_SetNextSection(UPawnAnimCombo::GetComboStartName(m_ComboIndex), UPawnAnimCombo::GetComboEndeName(m_ComboIndex));
		}
		else if (EComboType::Defence == m_ComboType)
		{
			AnimInstance->Montage_SetNextSection(TEXT("Start"), TEXT("Counter"));
		}
	}
}

void UPawnAnimCombo::SetEnableUpdateAnimMontage(bool EnableUpdateAnimMontage)
{
	if (IsValid(m_ComboMontage))
	{
		m_EnableUpdateMontage = EnableUpdateAnimMontage;
	}
}

bool UPawnAnimCombo::IsEnableUpdateAnimMontage() const
{
	return m_EnableUpdateMontage;
}