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
void PlaySoundAtLocation(class ABaseCharacter* BaseCharacter, USoundBase* Sound);

#define DIRECTION_FORWARD	0x01
#define DIRECTION_BACK		0x02
#define DIRECTION_LEFT		0x04
#define DIRECTION_RIGHT		0x08

template <typename Enumeration>
static FORCEINLINE FString GetEnumerationToString(const Enumeration InValue)
{
	return StaticEnum<Enumeration>()->GetNameStringByValue(static_cast<int64>(InValue));
}

template <typename Enumeration>
static FORCEINLINE FName GetEnumerationToName(const Enumeration InValue)
{
	return StaticEnum<Enumeration>()->GetNameByValue(static_cast<int64>(InValue));
}

template <typename Enumeration>
static FORCEINLINE Enumeration GetNameStringToEnumeration(const FString& String)
{
	int64 Value = StaticEnum<Enumeration>()->GetValueByNameString(String);

	if (INDEX_NONE == Value)
	{

	}

	return static_cast<Enumeration>(Value);
}

template <typename Enumeration>
int64 GetMaxEnumValue()
{
	return StaticEnum<Enumeration>()->GetMaxEnumValue();
}

template <typename Enumeration>
static FORCEINLINE Enumeration GetNameToEnumeration(const FName& Name)
{
	int64 Value = StaticEnum<Enumeration>()->GetValueByName(Name);

	if (INDEX_NONE == Value)
	{

	}

	return static_cast<Enumeration>(Value);
}

UENUM(BlueprintType)
enum class EBaseAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Death,
	Defence,
	Attack,
	Avoid,
	Roll,
	Finisher,
};

UENUM(BlueprintType)
enum class EBaseAnimState : uint8
{
	None,
	Start,
	CountEnd,
	End,
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
	Spearman,
};

UENUM(BlueprintType)
enum class EHumanClassType : uint8
{
	None,
	HeavyLancer,
	Spearman,
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	Shield,
};

UENUM(BlueprintType)
enum class EActorType : uint8
{
	None,
	Weapon,
	Movement,
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Lance,
	Spear,
	Shield,
};

UENUM(BlueprintType)
enum class EPlayerCharacterType : uint8
{
	MaleMannequin,
	FemaleMannequin,
	Haena,	
	Max,
};

UENUM(BlueprintType)
enum class ENPCCharacterType : uint8
{
	Paragon,
};

UENUM(BlueprintType)
enum class ENPCAIControllerType : uint8
{
	Paragon,
	Max,
};


UENUM(BlueprintType)
enum class EAIControllerType : uint8
{
	Base,
	Max,
};

UENUM(BlueprintType)
enum class EComboType : uint8
{
	None,
	Attack,
	Paring,
	Defence,
};

UENUM(BlueprintType)
enum class EAnimationNotifyType : uint8
{
	AttackStart,
	AttackEnd,
	DefenceStart,
	DefenceEnd,
	CastStart,
	CastEnd,
	LHandStart,
	LHandEnd,
	RHandStart,
	RHandEnd,
	LFootStart,
	LFootEnd,
	RFootStart,
	RFootEnd,
};

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Base,
	Human,
};

UENUM(BlueprintType)
enum class EActorControllerType : uint8
{
	None,
	BasePlayer,
	HumanPlayer,
	BaseAI,
};