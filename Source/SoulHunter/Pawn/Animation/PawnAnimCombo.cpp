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

void UPawnAnimCombo::SetAnimMontage(UAnimMontage* AnimMontage, EComboType ComboType)
{
	m_AnimMontage = AnimMontage;
	m_AnimMontageSectionIndex = 1;
	m_EnableUpdateMontage = false;
	m_ComboType = ComboType;
}

void UPawnAnimCombo::StartAnimMontage(UAnimInstance* AnimInstance)
{
	if (IsValid(m_AnimMontage))
	{
		AnimInstance->Montage_Play(m_AnimMontage);

		if (EComboType::Attack == m_ComboType)
		{
			AnimInstance->Montage_SetNextSection(UPawnAnimCombo::GetComboStartName(m_AnimMontageSectionIndex), UPawnAnimCombo::GetComboEndeName(m_AnimMontageSectionIndex));
		}
		else if (EComboType::Defence == m_ComboType)
		{
			LOG(TEXT("StartAnimMontage : Defence"));
			AnimInstance->Montage_SetNextSection(TEXT("Start"), TEXT("Loop"));
			AnimInstance->Montage_SetNextSection(TEXT("Loop"), TEXT("Loop"));
		}
		else if (EComboType::Paring == m_ComboType)
		{
			AnimInstance->Montage_SetNextSection(TEXT("Start"), TEXT("End"));
			//카운터 성공하면 아래와같이 진행한다.
			//AnimInstance->Montage_SetNextSection(TEXT("Start"), TEXT("Counter"));
		}
	}
}

void UPawnAnimCombo::UpdateAnimMontage(UAnimInstance* AnimInstance)
{
	if (IsValid(m_AnimMontage))
	{
		if (EComboType::Attack == m_ComboType)
		{
			FName NextMontageSectionName = UPawnAnimCombo::GetComboStartName(m_AnimMontageSectionIndex + 1);

			if (m_AnimMontage->IsValidSectionName(NextMontageSectionName))
			{
				AnimInstance->Montage_SetNextSection(UPawnAnimCombo::GetComboStartName(m_AnimMontageSectionIndex), NextMontageSectionName);
				AnimInstance->Montage_SetNextSection(NextMontageSectionName, UPawnAnimCombo::GetComboEndeName(m_AnimMontageSectionIndex + 1));
			}
		}
		else if (EComboType::Paring == m_ComboType)
		{
			//AnimInstance->Montage_SetNextSection(TEXT("Start"), TEXT("Counter"));
			FName SectionName = AnimInstance->Montage_GetCurrentSection();

			if (SectionName != TEXT("Counter"))
			{
				AnimInstance->Montage_JumpToSection(TEXT("Counter"));
			}
		}
		else if (EComboType::Defence == m_ComboType)
		{
			FName SectionName = AnimInstance->Montage_GetCurrentSection();

			if (SectionName != TEXT("Counter"))
			{
				AnimInstance->Montage_JumpToSection(TEXT("Counter"));
			}
		}
	}
}

void UPawnAnimCombo::EndAnimMontage(UAnimInstance* AnimInstance)
{
	if (EComboType::Defence == m_ComboType)
	{
		FName SectionName = AnimInstance->Montage_GetCurrentSection();

		if (SectionName == TEXT("Loop")
			|| SectionName == TEXT("Start"))
		{
			AnimInstance->Montage_JumpToSection(TEXT("End"));
		}
	}
}

void UPawnAnimCombo::SetEnableUpdateAnimMontage(bool EnableUpdateAnimMontage)
{
	if (IsValid(m_AnimMontage))
	{
		if (true == m_EnableUpdateMontage
			&& false == EnableUpdateAnimMontage)
		{
			m_AnimMontageSectionIndex++;
		}

		m_EnableUpdateMontage = EnableUpdateAnimMontage;
	}
}

bool UPawnAnimCombo::IsEnableUpdateAnimMontage() const
{
	return m_EnableUpdateMontage;
}

EComboType UPawnAnimCombo::GetComboType() const
{
	return m_ComboType;
}