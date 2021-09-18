// Fill out your copyright notice in the Description page of Project Settings.


#include "ParagonTerraCharacter.h"

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