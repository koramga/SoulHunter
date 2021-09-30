// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanCharacter.h"
#include "Animation/HumanAnimInstance.h"
#include "../../Controller/Player/BasePlayerController.h"
#include "../../GameInstance/BaseGameInstance.h"
#include "../../Actor/BaseActor.h"

AHumanCharacter::AHumanCharacter()
{
	m_HumanClassType = EHumanClassType::None;
	m_CharacterType = ECharacterType::Human;
}

void AHumanCharacter::SetHumanClassType(EHumanClassType HumanClassType)
{
	m_HumanClassType = HumanClassType;

	if (IsValid(m_HumanAnimInstance))
	{
		if (m_HumanAnimInstance->GetHumanClassType() != HumanClassType)
		{
			//if (DATATABLEMANAGER->SetPlayerVR(m_PlayerVR, m_PlayerCharacterType, HumanClassType))
			//{
			FName LSocketName;
			FName RSocketName;

			FString LMeshPath;
			FString RMeshPath;

			m_HumanAnimInstance->SetHumanClassType(HumanClassType);

			ABaseActor* LSocketActor = nullptr;
			ABaseActor* RSocketActor = nullptr;

			switch (HumanClassType)
			{
			case EHumanClassType::HeavyLancer:
				LSocketName = L"HeavyLancerWeaponSocket";
				LSocketActor = BASEGAMEINSTANCE->GetActorManager()->CreateActor(TEXT("Lance"), this);
				RSocketName = L"HeavyLancerShieldSocket";
				RSocketActor = BASEGAMEINSTANCE->GetActorManager()->CreateActor(TEXT("Shield"), this);
				break;

			case EHumanClassType::Spearman:
				LSocketName = L"SpearmanShieldSocket";
				LSocketActor = BASEGAMEINSTANCE->GetActorManager()->CreateActor(TEXT("Shield"), this);
				RSocketName = L"SpearmanWeaponSocket";
				RSocketActor = BASEGAMEINSTANCE->GetActorManager()->CreateActor(TEXT("Spear"), this);
				break;
			}

			//UStaticMesh* LMesh = LoadObject<UStaticMesh>(nullptr, *LMeshPath);
			//UStaticMesh* RMesh = LoadObject<UStaticMesh>(nullptr, *RMeshPath);
			//
			//if (IsValid(LMesh))
			//{
			//	m_LHandMeshComponent->SetStaticMesh(LMesh);
			//}
			//
			//if (IsValid(RMesh))
			//{
			//	m_RHandMeshComponent->SetStaticMesh(RMesh);
			//}

			if (IsValid(LSocketActor)
				&& false == LSocketName.IsNone())
			{
				LSocketActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, LSocketName);
				LSocketActor->SetTakeDamageCallback(this, &AHumanCharacter::WeaponActorTakeDamage);
			}

			if (IsValid(RSocketActor)
				&& false == RSocketName.IsNone())
			{
				RSocketActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, RSocketName);
				RSocketActor->SetTakeDamageCallback(this, &AHumanCharacter::WeaponActorTakeDamage);
			}

			PrintViewport(1.f, FColor::Red, GetEnumerationToString(m_HumanClassType));

			//bool Attach = m_LHandMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, LSocketName);
			//m_RHandMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, RSocketName);
		//}
		}
	}
}

// Called when the game starts or when sBaseed
void AHumanCharacter::BeginPlay()
{
	Super::BeginPlay();

	LOG(TEXT("HumanCharacter BeginPlay"));

	m_PlayerVR = NewObject<UPlayerVR>(this, UPlayerVR::StaticClass());

	m_HumanAnimInstance = Cast<UHumanAnimInstance>(GetMesh()->GetAnimInstance());

	if (m_HumanClassType != EHumanClassType::None)
	{
		SetHumanClassType(m_HumanClassType);
	}

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

void AHumanCharacter::WeaponActorTakeDamage(ABaseActor* BaseActor, float Damage, float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (EActorType::Weapon == BaseActor->GetActorType())
	{
		AWeaponActor* WeaponActor = Cast<AWeaponActor>(BaseActor);

		if (EWeaponType::Shield == WeaponActor->GetWeaponType())
		{
			if (m_DefenceOn)
			{
				LOG(TEXT("Counter On"));

				m_DilationTime = 1.f;
				GetWorldSettings()->SetTimeDilation(0.5f);

				m_HumanAnimInstance->SetEnableCounter(true);
			}
		}
	}
}
