// Fill out your copyright notice in the Description page of Project Settings.


#include "FemaleMannequin.h"

AFemaleMannequin::AFemaleMannequin()
{
	m_PlayerCharacterType = EPlayerCharacterType::MaleMannequin;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin_Female.SK_Mannequin_Female'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAssert(TEXT("AnimBlueprint'/Game/SoulHunter/Pawn/Player/Mannequin/Animation/BPMannequinAnimInstance.BPMannequinAnimInstance_C'"));

	if (AnimAssert.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimAssert.Class);
	}
}

void AFemaleMannequin::BeginPlay()
{
	Super::BeginPlay();
}

void AFemaleMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}