// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimCombo.h"
#include "BaseAnimInstance.h"

UBaseAnimCombo::UBaseAnimCombo()
{
	m_EnableUpdateMontage = false;
	m_ComboType = EComboType::None;
}

FName UBaseAnimCombo::GetComboStartName(int32 ComboIndex)
{
	return FName(*FString::Printf(TEXT("Combo%02dStart"), ComboIndex));
}

FName UBaseAnimCombo::GetComboEndeName(int32 ComboIndex)
{
	return FName(*FString::Printf(TEXT("Combo%02dEnd"), ComboIndex));
}

void UBaseAnimCombo::SetAnimMontage(UAnimMontage* AnimMontage, EComboType ComboType)
{
	m_AnimMontage = AnimMontage;
	m_AnimMontageSectionIndex = 1;
	m_EnableUpdateMontage = false;
	m_ComboType = ComboType;
}

void UBaseAnimCombo::StartAnimMontage(UAnimInstance* AnimInstance)
{
	if (IsValid(m_AnimMontage))
	{
		AnimInstance->Montage_Play(m_AnimMontage);

		if (EComboType::Attack == m_ComboType)
		{
			AnimInstance->Montage_SetNextSection(UBaseAnimCombo::GetComboStartName(m_AnimMontageSectionIndex), UBaseAnimCombo::GetComboEndeName(m_AnimMontageSectionIndex));
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

void UBaseAnimCombo::UpdateAnimMontage(UAnimInstance* AnimInstance)
{
	if (IsValid(m_AnimMontage))
	{
		if (EComboType::Attack == m_ComboType)
		{
			FName NextMontageSectionName = UBaseAnimCombo::GetComboStartName(m_AnimMontageSectionIndex + 1);

			if (m_AnimMontage->IsValidSectionName(NextMontageSectionName))
			{
				AnimInstance->Montage_SetNextSection(UBaseAnimCombo::GetComboStartName(m_AnimMontageSectionIndex), NextMontageSectionName);
				AnimInstance->Montage_SetNextSection(NextMontageSectionName, UBaseAnimCombo::GetComboEndeName(m_AnimMontageSectionIndex + 1));
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

void UBaseAnimCombo::EndAnimMontage(UAnimInstance* AnimInstance)
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

	m_AnimMontage = nullptr;
	m_ComboType = EComboType::None;
}

void UBaseAnimCombo::SetEnableUpdateAnimMontage(bool EnableUpdateAnimMontage)
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

bool UBaseAnimCombo::IsEnableUpdateAnimMontage() const
{
	return m_EnableUpdateMontage;
}

EComboType UBaseAnimCombo::GetComboType() const
{
	return m_ComboType;
}

