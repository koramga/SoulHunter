// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "../../Character/BaseCharacter.h"

ABasePlayerController::ABasePlayerController()
{
	static ConstructorHelpers::FClassFinder<UMatineeCameraShake> CameraShake(TEXT("Blueprint'/Game/SoulHunter/Camera/BPCameraShake.BPCameraShake_C'"));

	if (CameraShake.Succeeded())
	{
		m_CameraShake = CameraShake.Class;
	}
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_BaseCharacter = Cast<ABaseCharacter>(GetCharacter());
}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//Picking();

	if (IsValid(m_BaseCharacter))
	{
		float fDeltaX, fDeltaY;

		GetInputMouseDelta(fDeltaX, fDeltaY);

		//PrintViewport(1.f, FColor::Red, *FString::Printf(TEXT("%.2f, %.2f"), fDeltaX, fDeltaY));

		if (fDeltaX != 0.f)
		{
			//m_PlayerCharacter->AddArmYaw(fDeltaX);

			//float fYaw = 1.f;
			//
			//if (fDeltaX < 0.f)
			//{
			//	fYaw *= -1.f;
			//}
			//
			//if (IsLookInputIgnored())
			//{
			//	LOG(TEXT("LookInputIgnored.."));
			//}
			//
			//PrintViewport(1.f, FColor::Red, *FString::Printf(TEXT("Yaw : %.2f"), fYaw));

			if (EBaseAnimType::Attack != m_BaseCharacter->GetBaseAnimType()
				&& false == m_BaseCharacter->IsLockOn())
			{
				//AddYawInput(fDeltaX);

				//FRotator Rotator = m_PlayerCharacter->GetActorRotation();
				//
				//Rotator.Yaw += fDeltaX * 10.f;
				//
				//m_PlayerCharacter->SetActorRotation(Rotator.Quaternion());

				FRotator Rotator = m_BaseCharacter->GetActorRotation();

				Rotator.Yaw += fDeltaX;

				m_BaseCharacter->SetActorRotation(Rotator);
			}
			else
			{
			}
		}

		if (fDeltaY != 0.f)
		{
			m_BaseCharacter->AddArmPitch(fDeltaY);
		}		
	}

	//FRotator Rotator = m_PlayerCharacter->GetActorRotation();
	//
	//LOG(TEXT("%.2f, %.2f"), Rotator.Yaw, InputYawScale);

	UpdateRotation(DeltaTime);

	//LOG(TEXT("DeltaMouseXY : %.2f, %.2f"), fDeltaX, fDeltaY);
}

void ABasePlayerController::CameraShake()
{
	LOG(TEXT("Call Camera Shake"));
	ClientStartCameraShake(m_CameraShake);
}

void ABasePlayerController::__InputMoveForwardBack(float Scale)
{
	if (IsValid(m_BaseCharacter))
	{
		if (m_BaseCharacter->CanMove())
		{
			m_BaseCharacter->AddMovementInput(m_BaseCharacter->GetActorForwardVector(), Scale);
		}
	}
}

void ABasePlayerController::__InputMoveLeftRight(float Scale)
{
	if (IsValid(m_BaseCharacter))
	{
		if (m_BaseCharacter->CanMove())
		{
			if (Scale != 0.f)
			{
				FVector vForwardVector = m_BaseCharacter->GetActorForwardVector();

				const FRotator rot(0.f, 90 * Scale, 0.f);

				FVector vResult = rot.RotateVector(vForwardVector);

				//PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("%.2f, %.2f, %.2f : %.2f, %.2f, %.2f"), vForwardVector.X, vForwardVector.Y, vForwardVector.Z, vResult.X, vResult.Y, vResult.Z));

				m_BaseCharacter->AddMovementInput(vResult);
			}
		}
	}
}

void ABasePlayerController::__InputDirectionTypeKey(float Scale)
{
	if (IsValid(m_BaseCharacter))
	{
		if (Scale > 0)
		{
			int32 DirectionOffset = static_cast<int32>(Scale);
	
			//PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("Input : %d"), Value));
	
			m_BaseCharacter->SetDirection(DirectionOffset);
		}
	}
}

void ABasePlayerController::__InputCombinationTypeKey(float Scale)
{
	if (IsValid(m_BaseCharacter))
	{
		int32 Value = static_cast<int>(Scale);
	
		ECombinationType CombinationType = static_cast<ECombinationType>(Scale);
	
		m_BaseCharacter->SetCombinationType(CombinationType);
	}
}

void ABasePlayerController::__InputToggleWalkAndRun()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->SetToggleWalkAndRun();
	}
}

void ABasePlayerController::__InputToggleKey()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->SetTestToggle();
	}
}

void ABasePlayerController::__InputDefenceKey()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->SetBaseAnimType(EBaseAnimType::Defence);
	}
}

void ABasePlayerController::__InputDefenceReleaseKey()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->SetBaseAnimType(EBaseAnimType::Idle);
	}
}

void ABasePlayerController::__InputAttackKey()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->SetBaseAnimType(EBaseAnimType::Attack);
	}
}

void ABasePlayerController::__InputAvoidKey()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->SetBaseAnimType(EBaseAnimType::Avoid);
	}
}

void ABasePlayerController::__InputRollKey()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->SetBaseAnimType(EBaseAnimType::Roll);
	}
}

void ABasePlayerController::__InputLockOnKey()
{
	if (IsValid(m_BaseCharacter))
	{
		
	}
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveForwardBack"), this, &ABasePlayerController::__InputMoveForwardBack);
	InputComponent->BindAxis(TEXT("MoveLeftRight"), this, &ABasePlayerController::__InputMoveLeftRight);
	InputComponent->BindAxis(TEXT("DirectionTypeKey"), this, &ABasePlayerController::__InputDirectionTypeKey);
	InputComponent->BindAxis(TEXT("CombinationTypeKey"), this, &ABasePlayerController::__InputCombinationTypeKey);
	
	InputComponent->BindAction(TEXT("ToggleWalkAndRun"), EInputEvent::IE_Pressed,
		this, &ABasePlayerController::__InputToggleWalkAndRun);
	
	InputComponent->BindAction(TEXT("ToggleKey"), EInputEvent::IE_Pressed,
		this, &ABasePlayerController::__InputToggleKey);
	
	InputComponent->BindAction(TEXT("DefenceKey"), EInputEvent::IE_Pressed,
		this, &ABasePlayerController::__InputDefenceKey);
	
	InputComponent->BindAction(TEXT("DefenceKey"), EInputEvent::IE_Released,
		this, &ABasePlayerController::__InputDefenceReleaseKey);
	
	InputComponent->BindAction(TEXT("AttackKey"), EInputEvent::IE_Pressed,
		this, &ABasePlayerController::__InputAttackKey);
	
	InputComponent->BindAction(TEXT("AvoidKey"), EInputEvent::IE_DoubleClick,
		this, &ABasePlayerController::__InputAvoidKey);
	
	InputComponent->BindAction(TEXT("RollKey"), EInputEvent::IE_Pressed,
		this, &ABasePlayerController::__InputRollKey);
	
	InputComponent->BindAction(TEXT("LockOnKey"), EInputEvent::IE_Pressed,
		this, &ABasePlayerController::__InputLockOnKey);
}