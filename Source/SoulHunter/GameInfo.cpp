// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInfo.h"
#include "Pawn/Player/Controller/UserPlayerController.h"
#include "Pawn/PawnCharacter.h"

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
		AUserPlayerController* MainPlayerController = Cast<AUserPlayerController>(UGameplayStatics::GetPlayerController(World, 0));

		if (IsValid(MainPlayerController))
		{
			APawnCharacter* PawnCharacter = MainPlayerController->GetPawn<APawnCharacter>();

			if (IsValid(PawnCharacter))
			{
				float Volumn = 1.f;

				FVector PlayerLocation = PawnCharacter->GetActorLocation();

				float Distance = FVector::Distance(PlayerLocation, Location);

				Volumn -= (1.f / 2000.f * Distance);

				UGameplayStatics::PlaySoundAtLocation(World, Sound, PawnCharacter->GetActorLocation(), Volumn);
			}
		}
	}
}

void PlaySoundAtLocation(APawnCharacter* PawnCharacter, USoundBase* Sound)
{
	return PlaySoundAtLocation(PawnCharacter->GetWorld(), Sound, PawnCharacter->GetActorLocation());
}

FName ConvertPlayerClassTypeToName(EPlayerClassType PlayerClassType)
{
	switch (PlayerClassType)
	{
	case EPlayerClassType::HeavyLancer :
		return TEXT("HeavyLancer");

	case EPlayerClassType::Spearman:
		return TEXT("Spearman");
	}

	return TEXT("");
}

EPlayerClassType ConvertNameToPlayerClassType(const FName& Name)
{
	for (int i = 0; i < static_cast<int>(EPlayerClassType::Max); ++i)
	{
		EPlayerClassType Type = static_cast<EPlayerClassType>(i);

		if (ConvertPlayerClassTypeToName(Type) == Name)
		{
			return Type;
		}
	}

	return EPlayerClassType::Max;
}

FName ConvertPlayerCharacterTypeToName(EPlayerCharacterType PlayerCharacterType)
{
	switch (PlayerCharacterType)
	{
	case EPlayerCharacterType::MaleMannequin:
		return TEXT("MaleMannequin");

	case EPlayerCharacterType::FemaleMannequin:
		return TEXT("FemaleMannequin");

	case EPlayerCharacterType::Haena:
		return TEXT("Haena");
	}

	return TEXT("Max");
}

EPlayerCharacterType ConvertNameToPlayerCharacterType(const FName& Name)
{
	for (int i = 0; i < static_cast<int>(EPlayerCharacterType::Max); ++i)
	{
		EPlayerCharacterType Type = static_cast<EPlayerCharacterType>(i);

		if (ConvertPlayerCharacterTypeToName(Type) == Name)
		{
			return Type;
		}
	}

	return EPlayerCharacterType::Max;
}

FName ConvertPawnCharacterTypeToName(EPawnCharacterType PawnCharacterType)
{
	switch (PawnCharacterType)
	{
	case EPawnCharacterType::Player :
		return TEXT("Player");

	case EPawnCharacterType::NPC :
		return TEXT("NPC");
	}

	return TEXT("Max");
}

EPawnCharacterType ConvertNameToPawnCharacterType(const FName& Name)
{
	for (int i = 0; i < static_cast<int>(EPawnCharacterType::Max); ++i)
	{
		EPawnCharacterType Type = static_cast<EPawnCharacterType>(i);

		if (ConvertPawnCharacterTypeToName(Type) == Name)
		{
			return Type;
		}
	}

	return EPawnCharacterType::Max;
}

FName ConvertNPCCharacterTypeToName(ENPCCharacterType NPCCharacterType)
{
	switch (NPCCharacterType)
	{
	case ENPCCharacterType::Paragon:
		return TEXT("Paragon");
	}

	return TEXT("Max");
}

ENPCCharacterType ConvertNameToNPCCharacterType(const FName& Name)
{
	for (int i = 0; i < static_cast<int>(ENPCCharacterType::Max); ++i)
	{
		ENPCCharacterType Type = static_cast<ENPCCharacterType>(i);

		if (ConvertNPCCharacterTypeToName(Type) == Name)
		{
			return Type;
		}
	}

	return ENPCCharacterType::Max;
}
FName ConvertNPCAIControllerTypeToName(ENPCAIControllerType NPCAIController)
{
	switch (NPCAIController)
	{
	case ENPCAIControllerType::Paragon:
		return TEXT("Paragon");
	}

	return TEXT("Max");
}

ENPCAIControllerType ConvertNameToNPCAIControllerType(const FName& Name)
{
	for (int i = 0; i < static_cast<int>(ENPCCharacterType::Max); ++i)
	{
		ENPCAIControllerType Type = static_cast<ENPCAIControllerType>(i);

		if (ConvertNPCAIControllerTypeToName(Type) == Name)
		{
			return Type;
		}
	}

	return ENPCAIControllerType::Max;
}