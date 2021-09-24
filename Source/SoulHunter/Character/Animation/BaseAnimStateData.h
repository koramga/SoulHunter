// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "BaseAnimStateData.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UBaseAnimStateData : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EBaseAnimType		m_BaseAnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EBaseAnimState		m_BaseAnimState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	int32				m_Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	int32				m_EndCount;

public:
	void SetBaseAnimType(EBaseAnimType BaseAnimType);
	void SetBaseAnimState(EBaseAnimState BaseAnimState);
	void SetEndCount(int32 Count);
	void AddCount();

public:
	EBaseAnimState GetBaseAnimState() const
	{
		return m_BaseAnimState;
	}

	int32 GetCount() const
	{
		return m_Count;
	}

	int32 GetEndCount() const
	{
		return m_EndCount;
	}

public:
	bool IsFinishAnimation() const;
	void ResetCount();
	
};
