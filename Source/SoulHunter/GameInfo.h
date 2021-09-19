// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem/Public/NavigationPath.h"

/**
 * 
 */

DECLARE_LOG_CATEGORY_EXTERN(UE8, Log, All)
#define LOG_CALLINFO		(FString(__FUNCTION__) + TEXT("{") + FString::FromInt(__LINE__) + TEXT("}"))
#define LOG(Format, ...)	UE_LOG(UE8, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define BASEGAMEINSTANCE	Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())
#define PLAYERCONTROLLER	Cast<AUserPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))
#define DATATABLEMANAGER	BASEGAMEINSTANCE->GetDataTableManager()

void PrintViewport(float Duration, const FColor& Color, const FString& strText);
void PlaySoundAtLocation(UWorld* World, USoundBase* Sound, const FVector& Location);
void PlaySoundAtLocation(class APawnCharacter* PawnCharacter, USoundBase* Sound);

#define DIRECTION_FORWARD	0x01
#define DIRECTION_BACK		0x02
#define DIRECTION_LEFT		0x04
#define DIRECTION_RIGHT		0x08

UENUM(BlueprintType)
enum class EPawnAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Death,
	Defence,
	Attack,
	Avoid,
	Roll,
	Max,
};

UENUM(BlueprintType)
enum class EPawnAnimState : uint8
{
	None,
	Start,
	CountEnd,
	End,
	Max,
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class EDirection : uint8
{
	None,
	Forward = DIRECTION_FORWARD,
	Back = DIRECTION_BACK,
	Left = DIRECTION_LEFT,
	Right = DIRECTION_RIGHT,
};

UENUM(BlueprintType)
enum class ECombinationType : uint8
{
	None,
	Strong,			//°­°ø°Ý
};

UENUM(BlueprintType)
enum class EToggleWalkAndRun : uint8
{
	Walk,
	Run
};

UENUM(BlueprintType)
enum class EPlayerClassType : uint8
{
	HeavyLancer,
	Max,
};

FName ConvertPlayerClassTypeToName(EPlayerClassType PlayerClassType);
EPlayerClassType ConvertNameToPlayerClassType(const FName& Name);

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	Shield,
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Lance,
};

UENUM(BlueprintType)
enum class EPlayerCharacterType : uint8
{
	MaleMannequin,
	FemaleMannequin,
	Haena,	
	Max,
};

FName ConvertPlayerCharacterTypeToName(EPlayerCharacterType PlayerCharacterType);
EPlayerCharacterType ConvertNameToPlayerCharacterType(const FName& Name);

UENUM(BlueprintType)
enum class EPawnCharacterType : uint8
{
	Player,
	NPC,
	Max,
};

FName ConvertPawnCharacterTypeToName(EPawnCharacterType PawnCharacterType);
EPawnCharacterType ConvertNameToPawnCharacterType(const FName& Name);

UENUM(BlueprintType)
enum class ENPCCharacterType : uint8
{
	Paragon,
	Max,
};

FName ConvertNPCCharacterTypeToName(ENPCCharacterType NPCCharacterType);
ENPCCharacterType ConvertNameToNPCCharacterType(const FName& Name);

UENUM(BlueprintType)
enum class ENPCAIControllerType : uint8
{
	Paragon,
	Max,
};

FName ConvertNPCAIControllerTypeToName(ENPCAIControllerType NPCAIController);
ENPCAIControllerType ConvertNameToNPCAIControllerType(const FName& Name);

UENUM(BlueprintType)
enum class EComboType : uint8
{
	Attack,
	Defence,
};