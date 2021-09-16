// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TableRow/Class/ClassTableRow.h"
#include "../TableRow/Skill/SkillTableRow.h"
#include "../TableRow/Status/ClassStatusTableRow.h"
#include "UObject/NoExportTypes.h"
#include "ClassViewRow.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UClassViewRow : public UObject
{
	GENERATED_BODY()

private :
	const FClassTableRow*			m_ClassTableRow;
	const FClassStatusTableRow*		m_ClassStatusTableRow;
	TArray<const FSkillTableRow*>	m_SkillTableRows;

public :
	void Clear();

public :
	void SetClassTableRow(const FClassTableRow* ClassTableRow);
	void SetClassStatusTableRow(const FClassStatusTableRow* ClassStatusTableRow);
	void AddSkillTableRow(const FSkillTableRow* SkillTableRow);

public :
	const FClassTableRow* GetClassTableRow() const;
	const FClassStatusTableRow* GetClassStatusTableRow() const;
	const TArray<const FSkillTableRow*> GetSkillTableRow() const;
};
