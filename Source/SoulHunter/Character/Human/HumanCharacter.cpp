// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanCharacter.h"
#include "Animation/HumanAnimInstance.h"
#include "../../Controller/Player/BasePlayerController.h"
#include "../../GameInstance/BaseGameInstance.h"

AHumanCharacter::AHumanCharacter()
{
	m_HumanClassType = EHumanClassType::Max;
}

void AHumanCharacter::AddArmPitch(float Value)
{

}

void AHumanCharacter::SetHumanClassType(EHumanClassType PlayerClassType)
{

}

// Called when the game starts or when sBaseed
void AHumanCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_PlayerVR = NewObject<UPlayerVR>(this, UPlayerVR::StaticClass());

	m_HumanAnimInstance = Cast<UHumanAnimInstance>(GetMesh()->GetAnimInstance());

	SetHumanClassType(EHumanClassType::Spearman);

	m_ToggleWalkAndRun = EToggleWalkAndRun::Run;
	//m_PlayerAnimInstance->SetPlayerClassType(EPlayerClassType::Lance);

	GetCharacterMovement()->MaxWalkSpeed = 600;//m_PlayerVR->GetPlayerCharacterTableRow()->RunSpeed;

	m_DilationToggle = true;
	m_DefenceOn = false;
	m_DilationTime = 0.f;
}

// Called every frame
void AHumanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}