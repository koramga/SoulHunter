// Fill out your copyright notice in the Description page of Project Settings.


#include "MaleMannequin.h"

AMaleMannequin::AMaleMannequin()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAssert(TEXT("AnimBlueprint'/Game/SoulHunter/Character/Human/Mannequin/Animation/BPMannequinAnimInstance.BPMannequinAnimInstance_C'"));

	if (AnimAssert.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimAssert.Class);
	}
}

void AMaleMannequin::BeginPlay()
{
	Super::BeginPlay();
}

void AMaleMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

