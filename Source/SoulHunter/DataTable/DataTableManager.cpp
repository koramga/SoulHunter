// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableManager.h"

UDataTableManager::UDataTableManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerCharacterDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Pawn/Player/PlayerCharacterDataTable.PlayerCharacterDataTable'"));

	if (PlayerCharacterDataTableAsset.Succeeded())
		m_PlayerCharacterDataTable = PlayerCharacterDataTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerClassSkillDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Pawn/Player/PlayerClassSkillDataTable.PlayerClassSkillDataTable'"));

	if (PlayerClassSkillDataTableAsset.Succeeded())
		m_PlayerClassSkillDataTable = PlayerClassSkillDataTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerClassDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Pawn/Player/PlayerClassTR.PlayerClassTR'"));

	if (PlayerClassDataTableAsset.Succeeded())
		m_PlayerClassDataTable = PlayerClassDataTableAsset.Object;


	//static ConstructorHelpers::FObjectFinder<UDataTable> PlayerClassDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Class/ClassDataTable.ClassDataTable'"));
	//
	//if (PlayerClassDataTableAsset.Succeeded())
	//	m_PlayerClassDataTable = PlayerClassDataTableAsset.Object;
	//
	//static ConstructorHelpers::FObjectFinder<UDataTable> PlayerSkillDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Skill/SkillDataTable.SkillDataTable'"));
	//
	//if (PlayerSkillDataTableAsset.Succeeded())
	//	m_PlayerSkillDataTable = PlayerSkillDataTableAsset.Object;
	//
	//static ConstructorHelpers::FObjectFinder<UDataTable> PlayerClassStatusDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Status/ClassStatusDataTable.ClassStatusDataTable'"));
	//
	//if (PlayerClassStatusDataTableAsset.Succeeded())
	//	m_PlayerClassStatusDataTable = PlayerClassStatusDataTableAsset.Object;
	//
	//static ConstructorHelpers::FObjectFinder<UDataTable> StatusDataTableAsset(TEXT("DataTable'/Game/SoulHunter/DataTable/Status/StatusDataTable.StatusDataTable'"));
	//
	//if (StatusDataTableAsset.Succeeded())
	//	m_StatusDataTable = StatusDataTableAsset.Object;
}

void UDataTableManager::Init()
{

}

bool UDataTableManager::SetPlayerVR(UPlayerVR* PlayerVR, EPlayerCharacterType PlayerCharacterType, EPlayerClassType PlayerClassType) const
{
	if (IsValid(PlayerVR))
	{
		PlayerVR->Clear();

		FName ClassKey = ConvertPlayerClassTypeToName(PlayerClassType);
		FName CharacterKey = ConvertPlayerCharacterTypeToName(PlayerCharacterType);

		const FPlayerCharacterTR* PlayerCharacterTR = m_PlayerCharacterDataTable->FindRow<FPlayerCharacterTR>(CharacterKey, TEXT(""));

		if (nullptr == PlayerCharacterTR)
		{
			LOG(TEXT("PlayerCharacterTR <%s> find failed"), *CharacterKey.ToString());
			return false;
		}

		PlayerVR->SetPlayerCharacterTableRow(PlayerCharacterTR);

		const FPlayerClassTR* PlayerClassTR = m_PlayerClassDataTable->FindRow<FPlayerClassTR>(ClassKey, TEXT(""));

		if (nullptr == PlayerClassTR)
		{
			LOG(TEXT("PlayerClassTR <%s> find failed"), *ClassKey.ToString());
			return false;
		}

		PlayerVR->SetPlayerClassTableRow(PlayerClassTR);

		for (int i = 0; i < PlayerClassTR->SkillKeys.Num(); ++i)
		{
			const FPlayerClassSkillTR* PlayerClassSkillTR = m_PlayerClassSkillDataTable->FindRow<FPlayerClassSkillTR>(PlayerClassTR->SkillKeys[i], TEXT(""));

			if (nullptr == PlayerClassSkillTR)
			{
				LOG(TEXT("PlayerClassSkillTR <%s> Failed.."), *PlayerClassTR->SkillKeys[i].ToString());
				return false;
			}

			PlayerVR->AddPlayerClassSkillTableRow(PlayerClassSkillTR);
		}

		return true;
	}

	return false;
}