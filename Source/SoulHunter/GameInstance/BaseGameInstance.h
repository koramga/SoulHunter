// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Engine/GameInstance.h"
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

public :
	virtual void Init() override;
};