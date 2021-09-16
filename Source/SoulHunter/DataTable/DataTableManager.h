// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "TableRow/Pawn/Player/PlayerCharacterTR.h"
#include "TableRow/Pawn/Player/PlayerClassSkillTR.h"
#include "TableRow/Pawn/Player/PlayerClassTR.h"
#include "View/PlayerVR.h"
#include "UObject/NoExportTypes.h"
#include "DataTableManager.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UDataTableManager : public UObject
{
	GENERATED_BODY()

public :
	UDataTableManager();

private :
	UDataTable* m_PlayerCharacterDataTable;
	UDataTable* m_PlayerClassSkillDataTable;
	UDataTable* m_PlayerClassDataTable;

public :
	void Init();

public :
	bool SetPlayerVR(UPlayerVR* PlayerVR, EPlayerCharacterType PlayerCharacterType, EPlayerClassType PlayerClassType) const;
};
