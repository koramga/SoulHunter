// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableManager.h"

UDataTableManager::UDataTableManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> ClassDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Class/ClassTableRow.ClassTableRow'"));

	if (ClassDataTableAsset.Succeeded())
		m_ClassDataTable = ClassDataTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> SkillDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Skill/SkillTableRow.SkillTableRow'"));

	if (ClassDataTableAsset.Succeeded())
		m_SkillDataTable = SkillDataTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> ClassStatusDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Status/ClassStatusTableRow.ClassStatusTableRow'"));

	if (ClassDataTableAsset.Succeeded())
		m_ClassStatusDataTable = ClassStatusDataTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> StatusDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Status/StatusTableRow.StatusTableRow'"));

	if (ClassDataTableAsset.Succeeded())
		m_StatusDataTable = StatusDataTableAsset.Object;
}

void UDataTableManager::Init()
{

}