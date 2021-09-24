// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimNotifyState.h"
#include "../BaseCharacter.h"

UBaseAnimNotifyState::UBaseAnimNotifyState()
{

}

void UBaseAnimNotifyState::AddLoopAnimationSequence(const FName& Name, const FString& SoundPath)
{
	UBaseAnimNotifyStateData* NewData = NewObject<UBaseAnimNotifyStateData>(this, UBaseAnimNotifyStateData::StaticClass());

	if (IsValid(NewData))
	{
		NewData->SetSequenceName(Name);

		if (false == SoundPath.IsEmpty())
		{
			NewData->SetSoundPath(SoundPath);
		}

		m_LoopAnimationSequenceData.Add(NewData);
	}
}

void UBaseAnimNotifyState::AddEndAnimationSequence(const FName& Name, const FString& SoundPath)
{
	UBaseAnimNotifyStateData* NewData = NewObject<UBaseAnimNotifyStateData>(this, UBaseAnimNotifyStateData::StaticClass());

	if (IsValid(NewData))
	{
		NewData->SetSequenceName(Name);

		if (false == SoundPath.IsEmpty())
		{
			NewData->SetSoundPath(SoundPath);
		}

		m_EndAnimationSequenceData.Add(NewData);
	}
}

void UBaseAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ABaseCharacter* BaseCharacter = MeshComp->GetOwner<ABaseCharacter>();
	FVector SoundLocation = FVector::ZeroVector;
	
	if (IsValid(BaseCharacter))
	{
		m_BaseAnimType = BaseCharacter->GetBaseAnimType();
	}
	
	FString strSequenceName = Animation->GetName();
	FName SequenceName = FName(*strSequenceName);
	
	LOG(TEXT("NotifyBegin : <%s>"), *Animation->GetName());
	
	m_HasLoopAnimation = false;
	m_HasEndAnimation = false;
	
	for (UBaseAnimNotifyStateData* SequenceData : m_LoopAnimationSequenceData)
	{
		if (SequenceData->GetSequenceName() == SequenceName)
		{
			m_HasLoopAnimation = true;
	
			m_SequenceData = SequenceData;
	
			break;
		}
	}
	
	//LOG(TEXT("SequenceName <%s>"), *strSequenceName);
	
	for (UBaseAnimNotifyStateData* SequenceData : m_EndAnimationSequenceData)
	{
		if (SequenceData->GetSequenceName() == SequenceName)
		{
			m_HasEndAnimation = true;

			m_SequenceData = SequenceData;

			break;
		}
	}
	
	if (IsValid(m_SequenceData))
	{
		m_SequenceData->PlaySound(BaseCharacter);
	}
}

void UBaseAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (m_HasLoopAnimation)
	{
		m_DeltaTime += FrameDeltaTime;

		ABaseCharacter* BaseCharacter = MeshComp->GetOwner<ABaseCharacter>();

		if (IsValid(BaseCharacter))
		{
			if (m_DeltaTime >= Animation->GetPlayLength())
			{
				m_DeltaTime -= Animation->GetPlayLength();

				if (IsValid(m_SequenceData))
				{
					m_SequenceData->PlaySound(BaseCharacter);
				}

				BaseCharacter->AddEndAnimationState(m_BaseAnimType);
			}
		}
	}
}

void UBaseAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (IsValid(Animation))
	{
		LOG(TEXT("NotifyEnd : <%s>"), *Animation->GetName());
	}

	if (m_HasEndAnimation)
	{
		ABaseCharacter* BaseCharacter = MeshComp->GetOwner<ABaseCharacter>();

		if (IsValid(BaseCharacter))
		{
			BaseCharacter->SetEndAnimationState(m_BaseAnimType);
		}
	}
}


