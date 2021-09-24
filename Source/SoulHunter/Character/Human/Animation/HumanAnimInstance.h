// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Animation/BaseAnimInstance.h"
#include "HumanAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UHumanAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UHumanAnimInstance();

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EHumanClassType		m_HumanClassType;

public :
	EHumanClassType GetHumanClassType() const;
	void SetHumanClassType(EHumanClassType HumanClassType);
};
