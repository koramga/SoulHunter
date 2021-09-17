// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Animation/PlayerAnimInstance.h"
#include "../../Controller/User/UserPlayerController.h"
#include "../../GameInstance/BaseGameInstance.h"

APlayerCharacter::APlayerCharacter()
{
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	m_LHandMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LHandComponent"));
	m_RHandMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RHandComponent"));

	m_LHandMeshComponent->SetupAttachment(GetMesh());
	m_RHandMeshComponent->SetupAttachment(GetMesh());

	//Arm을 Root에 붙여준다.
	m_Arm->SetupAttachment(RootComponent);

	m_PlayerCharacterType = EPlayerCharacterType::Max;

	//

	//Camera를 Arm에 붙여준다.
	m_Camera->SetupAttachment(m_Arm);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_PlayerVR = NewObject<UPlayerVR>(this, UPlayerVR::StaticClass());

	m_PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	SetPlayerClassType(EPlayerClassType::HeavyLancer);

	//m_PlayerAnimInstance->SetPlayerClassType(EPlayerClassType::Lance);

	GetCharacterMovement()->MaxWalkSpeed = m_PlayerVR->GetPlayerCharacterTableRow()->WalkSpeed;

	m_DilationToggle = false;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EPawnAnimType PawnAnimType = m_PlayerAnimInstance->GetPawnAnimType();

	if (m_Speed == 0.f)
	{
		if (EPawnAnimType::Walk == PawnAnimType
			|| EPawnAnimType::Run == PawnAnimType)
		{
			m_PlayerAnimInstance->SetPawnAnimType(EPawnAnimType::Idle);
		}
	}

	//UpdateMoveAnimation();
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
		int32 Value = static_cast<int32>(Scale);

		if ((Value & 0x01) > 0)
		{
			//Forward
			m_PlayerAnimInstance->SetDirection(EDirection::Forward);
		}
		else if ((Value & 0x02) > 0)
		{
			//Back
			m_PlayerAnimInstance->SetDirection(EDirection::Back);
		}
		else if ((Value & 0x04) > 0)
		{
			//Left
			m_PlayerAnimInstance->SetDirection(EDirection::Left);
		}
		else if ((Value & 0x08) > 0)
		{
			//Right
			m_PlayerAnimInstance->SetDirection(EDirection::Right);
		}
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
	m_DilationToggle = !m_DilationToggle;

	if (m_DilationToggle)
	{
		GetWorldSettings()->SetTimeDilation(1.f);
	}
	else
	{
		GetWorldSettings()->SetTimeDilation(0.5f);
	}
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