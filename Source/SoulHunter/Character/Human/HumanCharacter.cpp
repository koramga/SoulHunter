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

	if (IsValid(m_LHandWeaponActor))
	{
		//LSocketActor 맞춰서 지워주기
		m_LHandWeaponActor->Destroy();
		m_LHandWeaponActor = nullptr;
	}

	if (IsValid(m_RHandWeaponActor))
	{
		//RSocketActor 맞춰서 지워주기
		m_RHandWeaponActor->Destroy();
		m_RHandWeaponActor = nullptr;
	}

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
				LSocketActor->SetOverlapBeginCallback(this, &AHumanCharacter::ActorOverlapBegin);
				m_LHandWeaponActor = Cast<AWeaponActor>(LSocketActor);
			}

			if (IsValid(RSocketActor)
				&& false == RSocketName.IsNone())
			{
				RSocketActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, RSocketName);
				RSocketActor->SetTakeDamageCallback(this, &AHumanCharacter::WeaponActorTakeDamage);
				RSocketActor->SetOverlapBeginCallback(this, &AHumanCharacter::ActorOverlapBegin);
				m_RHandWeaponActor = Cast<AWeaponActor>(RSocketActor);
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

	if (m_CounterTime > 0.f)
	{
		m_CounterTime -= DeltaTime;

		if (m_CounterTime <= 0.f)
		{
			PrintViewport(1.f, FColor::Blue, TEXT("Counter Off"));

			m_CounterTime = 0.f;

			GetWorldSettings()->SetTimeDilation(1.f);

			m_HumanAnimInstance->SetEnableCounter(false);

		}
	}
}

void AHumanCharacter::NotifyAnimation(EAnimationNotifyType AnimationNotifyType, EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType)
{
	Super::NotifyAnimation(AnimationNotifyType, BaseAnimType, Direction, CombinationType);



	if (EAnimationNotifyType::DefenceStart == AnimationNotifyType)
	{
		m_DefenceOn = true;
	}
	else if (EAnimationNotifyType::DefenceEnd == AnimationNotifyType)
	{
		//LOG(TEXT("Defence Off"));
		m_DefenceOn = false;

		m_BaseAnimInstance->SetEnableCounter(false);
	}
	else if (EAnimationNotifyType::LHandStart == AnimationNotifyType)
	{
		if (IsValid(m_LHandWeaponActor))
		{
			m_LHandWeaponActor->SetEnableCollision(true);
		}
	}
	else if (EAnimationNotifyType::LHandEnd == AnimationNotifyType)
	{
		if (IsValid(m_LHandWeaponActor))
		{
			m_LHandWeaponActor->SetEnableCollision(false);
		}
	}
	else if (EAnimationNotifyType::RHandStart == AnimationNotifyType)
	{
		if (IsValid(m_RHandWeaponActor))
		{
			m_RHandWeaponActor->SetEnableCollision(true);
		}

	}
	else if (EAnimationNotifyType::RHandEnd == AnimationNotifyType)
	{
		if (IsValid(m_RHandWeaponActor))
		{
			m_RHandWeaponActor->SetEnableCollision(false);
		}
	}
	else if (EAnimationNotifyType::LFootStart == AnimationNotifyType)
	{

	}
	else if (EAnimationNotifyType::LFootEnd == AnimationNotifyType)
	{

	}
	else if (EAnimationNotifyType::RFootStart == AnimationNotifyType)
	{

	}
	else if (EAnimationNotifyType::RFootEnd == AnimationNotifyType)
	{

	}
}

float AHumanCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (m_DefenceOn)
	{
		if (false == m_BaseAnimInstance->IsEnableCounter())
		{
			PrintViewport(1.f, FColor::Red, TEXT("Counter On"));

			m_BaseAnimInstance->SetEnableCounter(true);

			m_CounterTime = 0.5f;

			GetWorldSettings()->SetTimeDilation(0.5f);
		}
	}

	return Damage;
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

void AHumanCharacter::ActorOverlapBegin(class ABaseActor* BaseActor, const FHitResult& HitResult)
{
	if (this == HitResult.GetActor()->GetOwner())
	{
		return;
	}
	else
	{
		EActorType ActorType = BaseActor->GetActorType();

		if (EActorType::Weapon == ActorType)
		{
			AWeaponActor* WeaponActor = Cast<AWeaponActor>(BaseActor);

			if (EWeaponType::Shield != WeaponActor->GetWeaponType())
			{
				FDamageEvent DamageEvent;

				HitResult.Actor->TakeDamage(100.f, DamageEvent, GetController(), BaseActor);
			}
		}
	}
}