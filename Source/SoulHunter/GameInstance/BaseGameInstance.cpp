// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"

UBaseGameInstance::UBaseGameInstance()
{
	
}

void UBaseGameInstance::Init()
{
	Super::Init();	

	m_DataTableManager = NewObject<UDataTableManager>(this, UDataTableManager::StaticClass());

	if (IsValid(m_DataTableManager))
	{
		m_DataTableManager->Init();
	}
}

const UDataTableManager* UBaseGameInstance::GetDataTableManager() const
{
	return m_DataTableManager;
}