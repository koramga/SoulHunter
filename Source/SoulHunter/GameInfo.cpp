// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInfo.h"
#include "Controller/Player/BasePlayerController.h"
#include "Character/BaseCharacter.h"

DEFINE_LOG_CATEGORY(UE8)

void PrintViewport(float Duration, const FColor& Color, const FString& strText)
{
	GEngine->AddOnScreenDebugMessage(-1, Duration, Color, strText);
}

void PlaySoundAtLocation(UWorld* World, USoundBase* Sound, const FVector& Location)
{
	if (IsValid(World)
		&& IsValid(Sound))
	{
		ABasePlayerController* MainPlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(World, 0));

		if (IsValid(MainPlayerController))
		{
			ABaseCharacter* BaseCharacter = MainPlayerController->GetPawn<ABaseCharacter>();

			if (IsValid(BaseCharacter))
			{
				float Volumn = 1.f;

				FVector PlayerLocation = BaseCharacter->GetActorLocation();

				float Distance = FVector::Distance(PlayerLocation, Location);

				Volumn -= (1.f / 2000.f * Distance);

				UGameplayStatics::PlaySoundAtLocation(World, Sound, BaseCharacter->GetActorLocation(), Volumn);
			}
		}
	}
}

void PlaySoundAtLocation(class ABaseCharacter* BaseCharacter, USoundBase* Sound)
{
	return PlaySoundAtLocation(BaseCharacter->GetWorld(), Sound, BaseCharacter->GetActorLocation());
}