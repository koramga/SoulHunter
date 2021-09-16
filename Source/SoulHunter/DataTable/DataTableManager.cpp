// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableManager.h"

UDataTableManager::UDataTableManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> ClassDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Class/ClassDataTable.ClassDataTable'"));

	if (ClassDataTableAsset.Succeeded())
		m_ClassDataTable = ClassDataTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> SkillDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Skill/SkillDataTable.SkillDataTable'"));

	if (SkillDataTableAsset.Succeeded())
		m_SkillDataTable = SkillDataTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> ClassStatusDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Status/ClassStatusDataTable.ClassStatusDataTable'"));

	if (ClassStatusDataTableAsset.Succeeded())
		m_ClassStatusDataTable = ClassStatusDataTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> StatusDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Status/StatusDataTable.StatusDataTable'"));

	if (StatusDataTableAsset.Succeeded())
		m_StatusDataTable = StatusDataTableAsset.Object;
}

void UDataTableManager::Init()
{

}

bool UDataTableManager::SetClassViewRow(UClassViewRow* ClassViewRow, EPlayerClassType PlayerClassType) const
{
	if (IsValid(ClassViewRow))
	{
		ClassViewRow->Clear();

		do
		{
			FName Key = ConvertPlayerClassTypeToString(PlayerClassType);

			const FClassTableRow* ClassTableRow = m_ClassDataTable->FindRow<FClassTableRow>(Key, TEXT(""));

			if (nullptr == ClassTableRow)
			{
				LOG(TEXT("ClassTableRow <%s> Failed.."), *Key.ToString());
				break;
			}

			ClassViewRow->SetClassTableRow(ClassTableRow);

			const FClassStatusTableRow* ClassStatusTableRow = m_ClassStatusDataTable->FindRow<FClassStatusTableRow>(ClassTableRow->ClassStatusKey, TEXT(""));

			if (nullptr == ClassStatusTableRow)
			{
				LOG(TEXT("ClassStatusTableRow <%s> Failed.."), *ClassTableRow->ClassStatusKey.ToString());
				break;
			}

			ClassViewRow->SetClassStatusTableRow(ClassStatusTableRow);

			for (int i = 0; i < ClassTableRow->SkillKeys.Num(); ++i)
			{
				const FSkillTableRow* SkillTableRow = m_SkillDataTable->FindRow<FSkillTableRow>(ClassTableRow->SkillKeys[i], TEXT(""));

				if (nullptr == SkillTableRow)
				{
					LOG(TEXT("SkillTableRow <%s> Failed.."), *ClassTableRow->SkillKeys[i].ToString());
					goto EndClassViewRow;
				}

				ClassViewRow->AddSkillTableRow(SkillTableRow);
			}

			return true;

		} while (0);
	}

EndClassViewRow :

	LOG(TEXT("ClassViewRow Failed.."));

	return false;
}