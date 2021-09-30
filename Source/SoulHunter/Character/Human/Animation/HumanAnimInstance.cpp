// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanAnimInstance.h"

UHumanAnimInstance::UHumanAnimInstance()
{
	m_HumanClassType = EHumanClassType::Max;
}

EHumanClassType UHumanAnimInstance::GetHumanClassType() const
{
	return m_HumanClassType;
}

void UHumanAnimInstance::SetHumanClassType(EHumanClassType HumanClassType)
{
	m_HumanClassType = HumanClassType;
}