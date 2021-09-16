// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "TableRow/Class/ClassTableRow.h"
#include "TableRow/Skill/SkillTableRow.h"
#include "TableRow/Status/ClassStatusTableRow.h"
#include "TableRow/Status/StatusTableRow.h"
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
	UDataTable* m_ClassDataTable;
	UDataTable* m_SkillDataTable;
	UDataTable* m_ClassStatusDataTable;
	UDataTable* m_StatusDataTable;

public :
	void Init();

};
