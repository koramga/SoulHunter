// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimNotifyStateData.h"
#include "../BaseCharacter.h"

void UBaseAnimNotifyStateData::SetSequenceName(const FName& Name)
{
    m_SequenceName = Name;
}

void UBaseAnimNotifyStateData::SetSoundPath(const FString& Path)
{
    m_Sound = LoadObject<USoundBase>(this, *Path);
}

FName UBaseAnimNotifyStateData::GetSequenceName() const
{
    return m_SequenceName;
}

USoundBase* UBaseAnimNotifyStateData::GetSound() const
{
    return m_Sound;
}

void UBaseAnimNotifyStateData::PlaySound(UWorld* World, const FVector& Location)
{
    if (IsValid(m_Sound))
    {
        PlaySoundAtLocation(World, m_Sound, Location);
        //UGameplayStatics::PlaySoundAtLocation(World, m_Sound, Location);
    }
}

void UBaseAnimNotifyStateData::PlaySound(class ABaseCharacter* BaseCharacter)
{
    if (IsValid(m_Sound)
        && IsValid(BaseCharacter))
    {
        //AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(PawnCharacter->GetWorld(), 0));
        //
        //if (IsValid(MainPlayerController))
        //{
        //	APawnCharacter* PlayerPawnCharacter = MainPlayerController->GetPawn<APawnCharacter>();
        //
        //	if (IsValid(PlayerPawnCharacter))
        //	{
        //		float Volumn = 1.f;
        //
        //		FVector PlayerLocation = PlayerPawnCharacter->GetActorLocation();
        //
        //		float Distance = FVector::Distance(PlayerLocation, PawnCharacter->GetActorLocation()); 
        //
        //		Volumn -= (1 / 2000.f * Distance);
        //
        //        LOG(TEXT("Volumn : <%.2f> Distance : <%.2f>"), Volumn, Distance);
        //
        //		UGameplayStatics::PlaySoundAtLocation(PawnCharacter->GetWorld(), m_Sound, PawnCharacter->GetActorLocation(), Volumn);
        //	}
        //}

        PlaySoundAtLocation(BaseCharacter, m_Sound);
        //UGameplayStatics::PlaySoundAtLocation(PawnCharacter->GetWorld(), m_Sound, PawnCharacter->GetActorLocation(), 0.f, );
    }
}

