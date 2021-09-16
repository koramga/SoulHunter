// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "../../Animation/PawnAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UPlayerAnimInstance : public UPawnAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EPlayerClassType	m_PlayerClassType;

public :
	void SetPlayerClassType(EPlayerClassType PlayerClassType);
	EPlayerClassType GetPlayerClassType() const;
};
