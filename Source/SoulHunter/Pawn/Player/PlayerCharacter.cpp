// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Animation/PlayerAnimInstance.h"
#include "Controller/UserPlayerController.h"
#include "../../GameInstance/BaseGameInstance.h"

APlayerCharacter::APlayerCharacter()
{
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	m_LHandMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LHandComponent"));
	m_RHandMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RHandComponent"));

	m_LHandMeshComponent->SetupAttachment(GetMesh());
	m_RHandMeshComponent->SetupAttachment(GetMesh());

	//Arm�� Root�� �ٿ��ش�.
	m_Arm->SetupAttachment(RootComponent);

	m_PlayerCharacterType = EPlayerCharacterType::Max;

	bUseControllerRotationYaw = false;

	//Camera�� Arm�� �ٿ��ش�.
	m_Camera->SetupAttachment(m_Arm);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_PlayerVR = NewObject<UPlayerVR>(this, UPlayerVR::StaticClass());

	m_PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	SetPlayerClassType(EPlayerClassType::HeavyLancer);

	m_ToggleWalkAndRun = EToggleWalkAndRun::Run;
	//m_PlayerAnimInstance->SetPlayerClassType(EPlayerClassType::Lance);

	GetCharacterMovement()->MaxWalkSpeed = m_PlayerVR->GetPlayerCharacterTableRow()->RunSpeed;

	m_DilationToggle = true;

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
	if (false == m_LookAtMode)
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

		m_LookAtPawnCharacter = nullptr;

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
					m_LookAtPawnCharacter = PawnCharacter;
				}
			}
		}

#if ENABLE_DRAW_DEBUG

		// Draw debug line.
		FColor LineColor;

		if (IsValid(m_LookAtPawnCharacter)) LineColor = FColor::Red;
		else LineColor = FColor::Green;

		DrawDebugLine(
			GetWorld(),
			StartLocation,
			EndLocation,
			LineColor,
			false,
			1.f,
			0.f,
			10.f
		);

#endif
	}
	else
	{
		do
		{
			if (false == IsValid(m_LookAtPawnCharacter)
				|| m_LookAtPawnCharacter->IsDeath())
			{
				m_LookAtPawnCharacter = nullptr;
				m_LookAtMode = false;
				break;
			}
	
			//FVector ActorLocation = GetActorLocation();
			//
			//FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(ActorLocation, m_LookAtPawnCharacter->GetActorLocation());
			//
			//SetActorRotation(Rotator.Quaternion());
	
		} while (0);
	}

	//FVector ForwardVector = GetActorForwardVector();

	//LOG(TEXT("Forward<3> : <%.2f, %.2f, %.2f>"), GetActorForwardVector().X, GetActorForwardVector().Y, GetActorForwardVector().Z);

	//AUserPlayerController* UserPlayerController = GetController<AUserPlayerController>();
	//
	//float fDeltaX, fDeltaY;
	//
	//UserPlayerController->GetInputMouseDelta(fDeltaX, fDeltaY); 
	//
	//LOG(TEXT("DeltaX : <%.2f>"), fDeltaX * 10.f);
	//
	//FRotator Rotator = GetActorRotation();
	//Rotator.Yaw += fDeltaX;
	//
	//SetActorRotation(Rotator);

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

	PlayerInputComponent->BindAction(TEXT("AttackKey"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::__InputAttackKey);

	PlayerInputComponent->BindAction(TEXT("AvoidKey"), EInputEvent::IE_DoubleClick,
		this, &APlayerCharacter::__InputAvoidKey);

	PlayerInputComponent->BindAction(TEXT("RollKey"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::__InputRollKey);

	PlayerInputComponent->BindAction(TEXT("LookAtKey"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::__InputLookAtKey);

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

void APlayerCharacter::__InputLookAtKey()
{
	if (true == m_LookAtMode)
	{
		PrintViewport(1.f, FColor::Red, TEXT("LookAtMode OFF"));

		m_LookAtMode = false;
	}
	else
	{
		if (IsValid(m_LookAtPawnCharacter))
		{
			PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("LookAtMode ON <%s>"), *m_LookAtPawnCharacter->GetName()));

			m_LookAtMode = true;
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

			switch (PlayerClassType)
			{
			case EPlayerClassType::HeavyLancer:
				LSocketName = L"HeavyLancerWeaponSocket";
				LMeshPath = TEXT("StaticMesh'/Game/Heavy_Lancer_Set/mesh/SM_lance.SM_lance'");
				RSocketName = L"HeavyLancerShieldSocket";
				RMeshPath = TEXT("StaticMesh'/Game/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_Shield.SM_Shield'");
				break;
			}

			UStaticMesh* LMesh = LoadObject<UStaticMesh>(nullptr, *LMeshPath);
			UStaticMesh* RMesh = LoadObject<UStaticMesh>(nullptr, *RMeshPath);

			if (IsValid(LMesh))
			{
				m_LHandMeshComponent->SetStaticMesh(LMesh);
			}

			if (IsValid(RMesh))
			{
				m_RHandMeshComponent->SetStaticMesh(RMesh);
			}

			bool Attach = m_LHandMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, LSocketName);
			m_RHandMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, RSocketName);
		}
	}
}

bool APlayerCharacter::IsLookAtMode() const
{
	return m_LookAtMode;
}