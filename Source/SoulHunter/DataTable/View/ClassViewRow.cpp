// Fill out your copyright notice in the Description page of Project Settings.


#include "ClassViewRow.h"

void UClassViewRow::Clear()
{
	m_ClassTableRow = nullptr;
	m_ClassStatusTableRow = nullptr;

	m_SkillTableRows.Empty();
}

void UClassViewRow::SetClassTableRow(const FClassTableRow* ClassTableRow)
{
	m_ClassTableRow = ClassTableRow;
}

void UClassViewRow::SetClassStatusTableRow(const FClassStatusTableRow* ClassStatusTableRow)
{
	m_ClassStatusTableRow = ClassStatusTableRow;
}

void UClassViewRow::AddSkillTableRow(const FSkillTableRow* SkillTableRow)
{
	m_SkillTableRows.Add(SkillTableRow);
}

const FClassStatusTableRow* UClassViewRow::GetClassStatusTableRow() const
{
	return m_ClassStatusTableRow;
}

const FClassTableRow* UClassViewRow::GetClassTableRow() const
{
	return m_ClassTableRow;
}

const TArray<const FSkillTableRow*> UClassViewRow::GetSkillTableRow() const
{
	return m_SkillTableRows;
}


