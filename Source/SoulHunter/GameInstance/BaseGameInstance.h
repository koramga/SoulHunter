// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Engine/GameInstance.h"
#include "../DataTable/DataTableManager.h"
#include "../Actor/ActorManager.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public :
	UBaseGameInstance();

protected :
	UDataTableManager*	m_DataTableManager;
	UActorManager*		m_ActorManager;


public :
	virtual void Init() override;

public :
	const UDataTableManager* GetDataTableManager() const;
	const UActorManager* GetActorManager() const;
};