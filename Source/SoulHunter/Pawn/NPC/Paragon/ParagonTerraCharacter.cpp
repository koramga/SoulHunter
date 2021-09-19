// Fill out your copyright notice in the Description page of Project Settings.


#include "ParagonTerraCharacter.h"
#include "../../../GameInstance/BaseGameInstance.h"

AParagonTerraCharacter::AParagonTerraCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonTerra/Characters/Heroes/Terra/Meshes/Terra.Terra'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAssert(TEXT("AnimBlueprint'/Game/SoulHunter/Pawn/NPC/Paragon/Animation/BPParagonAnimInstance.BPParagonAnimInstance_C'"));
	
	if (AnimAssert.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimAssert.Class);
	}
}

void AParagonTerraCharacter::NotifyAnimation(EAnimationNotifyType AnimationNotifyType, EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType)
{
	LOG(TEXT("NotifyAnimation"));

	if (EAnimationNotifyType::AttackStart == AnimationNotifyType)
	{
		if (EPawnAnimType::Attack == PawnAnimType)
		{
			if ((Direction & DIRECTION_FORWARD) > 0)
			{
				ABaseActor* BaseActor = BASEGAMEINSTANCE->GetActorManager()->CreateActor(TEXT("Sphere"), this, GetActorLocation() + GetActorForwardVector() * 100, GetActorRotation());
			}
		}
	}
}