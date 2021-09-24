// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimStateData.h"

void UBaseAnimStateData::SetBaseAnimType(EBaseAnimType BaseAnimType)
{
    m_BaseAnimType = BaseAnimType;
}

void UBaseAnimStateData::SetBaseAnimState(EBaseAnimState BaseAnimState)
{
    m_BaseAnimState = BaseAnimState;
}

void UBaseAnimStateData::SetEndCount(int32 Count)
{
    m_EndCount = Count;
}

void UBaseAnimStateData::AddCount()
{
    m_Count++;
}

bool UBaseAnimStateData::IsFinishAnimation() const
{
    if (m_Count >= m_EndCount)
    {
        return true;
    }

    return false;
}

void UBaseAnimStateData::ResetCount()
{
    m_Count = 0;
}

