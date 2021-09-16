// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	m_PlayerClassType = EPlayerClassType::None;
}

void UPlayerAnimInstance::SetPlayerClassType(EPlayerClassType PlayerClassType)
{
	m_PlayerClassType = PlayerClassType;
}

EPlayerClassType UPlayerAnimInstance::GetPlayerClassType() const
{
	return m_PlayerClassType;
}