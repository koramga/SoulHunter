// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerVR.h"

void UPlayerVR::Clear()
{
	m_PlayerCharacterTR = nullptr;
	m_PlayerClassTR = nullptr;

	m_PlayerClassSkillTableRows.Empty();
}

void UPlayerVR::SetPlayerCharacterTableRow(const FPlayerCharacterTR* PlayerCharacterTR)
{
	m_PlayerCharacterTR = PlayerCharacterTR;
}

void UPlayerVR::SetPlayerClassTableRow(const FPlayerClassTR* PlayerClassTR)
{
	m_PlayerClassTR = PlayerClassTR;
}

void UPlayerVR::AddPlayerClassSkillTableRow(const FPlayerClassSkillTR* PlayerClassSkillTR)
{
	m_PlayerClassSkillTableRows.Add(PlayerClassSkillTR);
}

const FPlayerCharacterTR* UPlayerVR::GetPlayerCharacterTableRow() const
{
	return m_PlayerCharacterTR;
}

const FPlayerClassTR* UPlayerVR::GetPlayerClassTableRow() const
{
	return m_PlayerClassTR;
}

const TArray<const FPlayerClassSkillTR*>& UPlayerVR::GetPlayerSkillTableRow() const
{
	return m_PlayerClassSkillTableRows;
}