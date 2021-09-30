// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimState.h"

UBaseAnimState::UBaseAnimState()
{

}

bool UBaseAnimState::CreateAnimationState(EBaseAnimType BaseAnimType)
{
	UBaseAnimStateData* BaseAnimStateData = m_mapBaseAnimStateData.FindRef(BaseAnimType);

	if (IsValid(BaseAnimStateData))
	{
		return false;
	}

	BaseAnimStateData = NewObject<UBaseAnimStateData>(this, UBaseAnimStateData::StaticClass());

	BaseAnimStateData->SetBaseAnimType(BaseAnimType);
	BaseAnimStateData->SetBaseAnimState(EBaseAnimState::None);
	BaseAnimStateData->SetEndCount(1);

	m_mapBaseAnimStateData.Add(BaseAnimType, BaseAnimStateData);

	return true;
}

void UBaseAnimState::SetAnimationStateEndCount(EBaseAnimType BaseAnimType, int32 Count)
{
	UBaseAnimStateData* BaseAnimStateData = m_mapBaseAnimStateData.FindRef(BaseAnimType);

	if (IsValid(BaseAnimStateData))
	{
		BaseAnimStateData->SetEndCount(Count);
	}
}

void UBaseAnimState::SetStartAnimationState(EBaseAnimType BaseAnimType)
{
	UBaseAnimStateData* BaseAnimStateData = m_mapBaseAnimStateData.FindRef(BaseAnimType);

	if (IsValid(BaseAnimStateData))
	{
		BaseAnimStateData->SetBaseAnimState(EBaseAnimState::Start);
	}
}

void UBaseAnimState::AddEndAnimationState(EBaseAnimType BaseAnimType)
{
	UBaseAnimStateData* BaseAnimStateData = m_mapBaseAnimStateData.FindRef(BaseAnimType);

	if (IsValid(BaseAnimStateData))
	{
		if (EBaseAnimState::Start == BaseAnimStateData->GetBaseAnimState())
		{
			BaseAnimStateData->AddCount();

			if (BaseAnimStateData->GetCount() >= BaseAnimStateData->GetEndCount())
			{
				BaseAnimStateData->SetBaseAnimState(EBaseAnimState::CountEnd);
			}
		}
	}
}

void UBaseAnimState::SetEndAnimationState(EBaseAnimType BaseAnimType)
{
	UBaseAnimStateData* BaseAnimStateData = m_mapBaseAnimStateData.FindRef(BaseAnimType);

	if (IsValid(BaseAnimStateData))
	{
		if (EBaseAnimState::None != BaseAnimStateData->GetBaseAnimState())
		{
			BaseAnimStateData->SetBaseAnimState(EBaseAnimState::End);
		}
	}
}

void UBaseAnimState::ResetAnimationState(EBaseAnimType BaseAnimType)
{
	UBaseAnimStateData* BaseAnimStateData = m_mapBaseAnimStateData.FindRef(BaseAnimType);

	if (IsValid(BaseAnimStateData))
	{
		BaseAnimStateData->SetBaseAnimState(EBaseAnimState::None);
		BaseAnimStateData->ResetCount();
	}
}

EBaseAnimState UBaseAnimState::GetAnimationState(EBaseAnimType BaseAnimType)
{
	UBaseAnimStateData* BaseAnimStateData = m_mapBaseAnimStateData.FindRef(BaseAnimType);

	if (IsValid(BaseAnimStateData))
	{
		return BaseAnimStateData->GetBaseAnimState();
	}

	return EBaseAnimState::None;
}

bool UBaseAnimState::IsFinishAnimationState(EBaseAnimType BaseAnimType) const
{
	UBaseAnimStateData* BaseAnimStateData = m_mapBaseAnimStateData.FindRef(BaseAnimType);

	if (IsValid(BaseAnimStateData))
	{
		return BaseAnimStateData->IsFinishAnimation();
	}

	return false;
}

