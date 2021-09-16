// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TableRow/Pawn/Player/PlayerCharacterTR.h"
#include "../TableRow/Pawn/Player/PlayerClassSkillTR.h"
#include "../TableRow/Pawn/Player/PlayerClassTR.h"
#include "UObject/NoExportTypes.h"
#include "PlayerVR.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UPlayerVR : public UObject
{
	GENERATED_BODY()

private :
	const FPlayerCharacterTR*			m_PlayerCharacterTR;
	const FPlayerClassTR*				m_PlayerClassTR;
	TArray<const FPlayerClassSkillTR*>	m_PlayerClassSkillTableRows;

public :
	void Clear();

public :
	void SetPlayerCharacterTableRow(const FPlayerCharacterTR* PlayerCharacterTR);
	void SetPlayerClassTableRow(const FPlayerClassTR* PlayerClassTR);
	void AddPlayerClassSkillTableRow(const FPlayerClassSkillTR* PlayerClassSkillTR);
	//void SetPlayerClassStatusTableRow(const FPlayerClassStatusTableRow* ClassStatusTableRow);
	//void SetPlayerClassTableRow(const FPlayerClassTableRow* ClassTableRow);
	//void AddPlayerSkillTableRow(const FPlayerSkillTableRow* SkillTableRow);

public :
	const FPlayerCharacterTR* GetPlayerCharacterTableRow() const;
	const FPlayerClassTR* GetPlayerClassTableRow() const;
	const TArray<const FPlayerClassSkillTR*>& GetPlayerSkillTableRow() const;
};
