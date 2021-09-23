// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Animation/PlayerAnimInstance.h"
#include "Controller/UserPlayerController.h"
#include "../../GameInstance/BaseGameInstance.h"

APlayerCharacter::APlayerCharacter()
{
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	//Arm을 Root에 붙여준다.
	m_Arm->SetupAttachment(RootComponent);

	m_PlayerCharacterType = EPlayerCharacterType::Max;

	bUseControllerRotationYaw = false;

	//Camera를 Arm에 붙여준다.
	m_Camera->SetupAttachment(m_Arm);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_PlayerVR = NewObject<UPlayerVR>(this, UPlayerVR::StaticClass());

	m_PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	SetPlayerClassType(EPlayerClassType::Spearman);

	m_ToggleWalkAndRun = EToggleWalkAndRun::Run;
	//m_PlayerAnimInstance->SetPlayerClassType(EPlayerClassType::Lance);

	GetCharacterMovement()->MaxWalkSpeed = m_PlayerVR->GetPlayerCharacterTableRow()->RunSpeed;

	m_DilationToggle = true;
	m_DefenceOn = false;
	m_DilationTime = 0.f;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//LOG(TEXT("Forward<1> : <%.2f, %.2f, %.2f>"), GetActorForwardVector().X, GetActorForwardVector().Y, GetActorForwardVector().Z);

//	EPawnAnimType PawnAnimType = m_PlayerAnimInstance->GetPawnAnimType();
//
//	if (m_Speed == 0.f)
//	{
//		if (EPawnAnimType::Walk == PawnAnimType
//			|| EPawnAnimType::Run == PawnAnimType)
//		{
//			m_PlayerAnimInstance->SetPawnAnimType(EPawnAnimType::Idle);
//		}
//	}
//
	if (false == m_LockOn)
	{
		FVector ActorLocation = GetActorLocation();
		FVector StartLocation{ ActorLocation.X, ActorLocation.Y, ActorLocation.Z };    // Raytrace starting point.
		FVector EndLocation = ActorLocation + GetActorForwardVector() * 2000.f;

		FCollisionQueryParams param;

		param.AddIgnoredActor(this);

		// Raytrace for overlapping actors.
		TArray<FHitResult> HitResults;
		GetWorld()->LineTraceMultiByObjectType(
			OUT HitResults,
			StartLocation,
			EndLocation,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
			param
		);

		m_LockOnPawnCharacter = nullptr;

		float MinimumDistance = FLT_MAX;

		for (FHitResult HitResult : HitResults)
		{
			APawnCharacter* PawnCharacter = Cast<APawnCharacter>(HitResult.Actor);

			if (IsValid(PawnCharacter))
			{
				float Distance = FVector::Distance(ActorLocation, PawnCharacter->GetActorLocation());

				if (MinimumDistance > Distance)
				{
					MinimumDistance = Distance;
					m_LockOnPawnCharacter = PawnCharacter;
				}
			}
		}

//#if ENABLE_DRAW_DEBUG
//
//		// Draw debug line.
//		FColor LineColor;
//
//		if (IsValid(m_LockOnPawnCharacter)) LineColor = FColor::Red;
//		else LineColor = FColor::Green;
//
//		DrawDebugLine(
//			GetWorld(),
//			StartLocation,
//			EndLocation,
//			LineColor,
//			false,
//			1.f,
//			0.f,
//			10.f
//		);
//
//#endif
	}
	else
	{
		if (false == IsValid(m_LockOnPawnCharacter)
			|| m_LockOnPawnCharacter->IsDeath())
		{
			m_LockOnPawnCharacter = nullptr;
			m_LockOn = false;
		}
	}

	if (m_DilationTime > 0.f)
	{
		m_DilationTime -= DeltaTime;

		if (m_DilationTime <= 0.f)
		{
			GetWorldSettings()->SetTimeDilation(1.f);
		}
	}

	//PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("Speed : <%.2f>, WalkSpeed : <%.2f>"), m_Speed, m_PlayerVR->GetPlayerCharacterTableRow()->RunSpeed));

	UpdateMoveAnimation();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForwardBack"), this, &APlayerCharacter::__InputMoveForwardBack);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &APlayerCharacter::__InputMoveLeftRight);
	PlayerInputComponent->BindAxis(TEXT("DirectionTypeKey"), this, &APlayerCharacter::__InputDirectionTypeKey);
	PlayerInputComponent->BindAxis(TEXT("CombinationTypeKey"), this, &APlayerCharacter::__InputCombinationTypeKey);

	PlayerInputComponent->BindAction(TEXT("ToggleWalkAndRun"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::__InputToggleWalkAndRun);

	PlayerInputComponent->BindAction(TEXT("ToggleKey"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::__InputToggleKey);

	PlayerInputComponent->BindAction(TEXT("DefenceKey"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::__InputDefenceKey);

	PlayerInputComponent->BindAction(TEXT("DefenceKey"), EInputEvent::IE_Released,
		this, &APlayerCharacter::__InputDefenceReleaseKey);

	PlayerInputComponent->BindAction(TEXT("AttackKey"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::__InputAttackKey);

	PlayerInputComponent->BindAction(TEXT("AvoidKey"), EInputEvent::IE_DoubleClick,
		this, &APlayerCharacter::__InputAvoidKey);

	PlayerInputComponent->BindAction(TEXT("RollKey"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::__InputRollKey);

	PlayerInputComponent->BindAction(TEXT("LockOnKey"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::__InputLockOnKey);

	//PlayerInputComponent->BindAction(TEXT("AttackKey"), EInputEvent::IE_Pressed,
	//	this, &APlayerCharacter::__InputAttackKey);
	//
	//PlayerInputComponent->BindAction(TEXT("AttackKey"), EInputEvent::IE_Pressed,
	//	this, &APlayerCharacter::__InputAttackKey);
	//
	//PlayerInputComponent->BindAction(TEXT("AttackKey"), EInputEvent::IE_Pressed,
	//	this, &APlayerCharacter::__InputAttackKey);
	
	//PlayerInputComponent->BindAction(TEXT("Attack01"), EInputEvent::IE_Pressed,
	//	this, &ADragonCharacter::__Attack01);
	//PlayerInputComponent->BindAction(TEXT("Attack02"), EInputEvent::IE_Pressed,
	//	this, &ADragonCharacter::__Attack02);

}

bool APlayerCharacter::CanMove()
{
	EPawnAnimType PawnAnimType = m_PlayerAnimInstance->GetPawnAnimType();

	if (EPawnAnimType::Idle == PawnAnimType
		|| EPawnAnimType::Walk == PawnAnimType
		|| EPawnAnimType::Run == PawnAnimType)
	{
		return true;
	}

	return false;
}

void APlayerCharacter::UpdateMoveAnimation()
{
	EPawnAnimType PawnAnimType = m_PlayerAnimInstance->GetPawnAnimType();

	if (m_Speed > 0.f)
	{
		if (EPawnAnimType::Idle == PawnAnimType)
		{
			if (EToggleWalkAndRun::Walk == m_ToggleWalkAndRun)
			{
				m_PlayerAnimInstance->SetPawnAnimType(EPawnAnimType::Walk);
			}
			else if (EToggleWalkAndRun::Run == m_ToggleWalkAndRun)
			{
				m_PlayerAnimInstance->SetPawnAnimType(EPawnAnimType::Run);
			}
		}
		else if (EPawnAnimType::Run == PawnAnimType)
		{
			if (EToggleWalkAndRun::Walk == m_ToggleWalkAndRun)
			{
				m_PlayerAnimInstance->SetPawnAnimType(EPawnAnimType::Walk);
			}
		}
		else if (EPawnAnimType::Walk == PawnAnimType)
		{
			if (EToggleWalkAndRun::Run == m_ToggleWalkAndRun)
			{
				m_PlayerAnimInstance->SetPawnAnimType(EPawnAnimType::Run);
			} 
		}
	}
}

void APlayerCharacter::NotifyAnimation(EAnimationNotifyType AnimationNotifyType, EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType)
{
	if (EAnimationNotifyType::DefenceStart == AnimationNotifyType)
	{
		LOG(TEXT("Defence On"));
		m_DefenceOn = true;
	}
	else if (EAnimationNotifyType::DefenceEnd == AnimationNotifyType)
	{
		LOG(TEXT("Defence Off"));
		m_DefenceOn = false;

		m_PawnAnimInstance->SetEnableCounter(false);
	}
}

void APlayerCharacter::WeaponActorTakeDamage(ABaseActor* BaseActor, float Damage, float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
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

				m_PawnAnimInstance->SetEnableCounter(true);
			}
		}
	}
}

void APlayerCharacter::__InputMoveForwardBack(float Scale)
{
	if (CanMove())
	{
		UpdateMoveAnimation();
		AddMovementInput(GetActorForwardVector(), Scale);
	}
}

void APlayerCharacter::__InputMoveLeftRight(float Scale)
{
	if (CanMove())
	{
		UpdateMoveAnimation();

		if (Scale != 0.f)
		{
			FVector vForwardVector = GetActorForwardVector();

			const FRotator rot(0.f, 90 * Scale, 0.f);

			FVector vResult = rot.RotateVector(vForwardVector);

			//PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("%.2f, %.2f, %.2f : %.2f, %.2f, %.2f"), vForwardVector.X, vForwardVector.Y, vForwardVector.Z, vResult.X, vResult.Y, vResult.Z));

			AddMovementInput(vResult);
		}
	}
}

void APlayerCharacter::__InputDirectionTypeKey(float Scale)
{
	if (Scale > 0)
	{
		int32 DirectionOffset = static_cast<int32>(Scale);

		//PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("Input : %d"), Value));

		m_PlayerAnimInstance->SetDirection(DirectionOffset);
	}
}

void APlayerCharacter::__InputCombinationTypeKey(float Scale)
{
	int32 Value = static_cast<int>(Scale);

	ECombinationType CombinationType = static_cast<ECombinationType>(Scale);

	m_PlayerAnimInstance->SetCombinationType(CombinationType);
}

void APlayerCharacter::__InputToggleWalkAndRun()
{
	if (EToggleWalkAndRun::Walk == m_ToggleWalkAndRun)
	{
		m_ToggleWalkAndRun = EToggleWalkAndRun::Run;

		GetCharacterMovement()->MaxWalkSpeed = m_PlayerVR->GetPlayerCharacterTableRow()->RunSpeed;
	}
	else if (EToggleWalkAndRun::Run == m_ToggleWalkAndRun)
	{
		m_ToggleWalkAndRun = EToggleWalkAndRun::Walk;

		GetCharacterMovement()->MaxWalkSpeed = m_PlayerVR->GetPlayerCharacterTableRow()->WalkSpeed;
	}

	UpdateMoveAnimation();
}

void APlayerCharacter::__InputToggleKey()
{
	LOG(TEXT("Rotator Changed.."));

	static float Yaw = 30.f;

	FRotator Rotator = GetActorRotation();

	Rotator.Yaw += Yaw;

	SetActorRotation(Rotator);

	//m_DilationToggle = !m_DilationToggle;
	//
	//if (m_DilationToggle)
	//{
	//	GetWorldSettings()->SetTimeDilation(1.f);
	//}
	//else
	//{
	//	GetWorldSettings()->SetTimeDilation(0.5f);
	//}


}

void APlayerCharacter::__InputDefenceKey()
{
	//PLAYERCONTROLLER->CameraShake();
	//UGameplayStatics::PlayWorldCameraShake(GetWorld(), )

	m_PlayerAnimInstance->SetPawnAnimType(EPawnAnimType::Defence);
}

void APlayerCharacter::__InputDefenceReleaseKey()
{
	m_PlayerAnimInstance->SetPawnAnimType(EPawnAnimType::Idle);
}

void APlayerCharacter::__InputAttackKey()
{
	//PrintViewport(1.f, FColor::Red, TEXT("AttackKey"));
	m_PlayerAnimInstance->SetPawnAnimType(EPawnAnimType::Attack);
}

void APlayerCharacter::__InputAvoidKey()
{
	m_PlayerAnimInstance->SetPawnAnimType(EPawnAnimType::Avoid);
}

void APlayerCharacter::__InputRollKey()
{
	m_PlayerAnimInstance->SetPawnAnimType(EPawnAnimType::Roll);
}

void APlayerCharacter::__InputLockOnKey()
{
	if (true == m_LockOn)
	{
		PrintViewport(1.f, FColor::Red, TEXT("Lock Off"));

		m_LockOn = false;
	}
	else
	{
		if (IsValid(m_LockOnPawnCharacter))
		{
			PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("Lock On <%s>"), *m_LockOnPawnCharacter->GetName()));

			m_LockOn = true;
		}
	}
}

void APlayerCharacter::AddArmPitch(float Value)
{
	FRotator Rotator = m_Arm->GetRelativeRotation();

	Rotator.Pitch += Value;

	if (Rotator.Pitch > 90.f)
	{
		Rotator.Pitch = 90.f;
	}
	else if (Rotator.Pitch < -90.f)
	{
		Rotator.Pitch = -90.f;
	}

	m_Arm->SetRelativeRotation(Rotator);
}

void APlayerCharacter::SetPlayerClassType(EPlayerClassType PlayerClassType)
{
	if (m_PlayerAnimInstance->GetPlayerClassType() != PlayerClassType)
	{
		if (DATATABLEMANAGER->SetPlayerVR(m_PlayerVR, m_PlayerCharacterType, PlayerClassType))
		{
			FName LSocketName;
			FName RSocketName;

			FString LMeshPath;
			FString RMeshPath;

			m_PlayerAnimInstance->SetPlayerClassType(PlayerClassType);

			ABaseActor* LSocketActor = nullptr;
			ABaseActor* RSocketActor = nullptr;

			switch (PlayerClassType)
			{
			case EPlayerClassType::HeavyLancer:
				LSocketName = L"HeavyLancerWeaponSocket";
				LSocketActor = BASEGAMEINSTANCE->GetActorManager()->CreateActor(TEXT("Lance"), this);
				RSocketName = L"HeavyLancerShieldSocket";
				RSocketActor = BASEGAMEINSTANCE->GetActorManager()->CreateActor(TEXT("Shield"), this);
				break;

			case EPlayerClassType::Spearman :
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
				LSocketActor->SetTakeDamageCallback(this, &APlayerCharacter::WeaponActorTakeDamage);
			}

			if (IsValid(RSocketActor)
				&& false == RSocketName.IsNone())
			{
				RSocketActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, RSocketName);
				RSocketActor->SetTakeDamageCallback(this, &APlayerCharacter::WeaponActorTakeDamage);
			}

			//bool Attach = m_LHandMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, LSocketName);
			//m_RHandMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, RSocketName);
		}
	}
}