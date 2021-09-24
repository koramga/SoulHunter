// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Animation/BaseAnimInstance.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	//Arm을 Root에 붙여준다.
	m_Arm->SetupAttachment(RootComponent);

	//Camera를 Arm에 붙여준다.
	m_Camera->SetupAttachment(m_Arm);

	m_ToggleWalkAndRun = EToggleWalkAndRun::Run;

	//bUseControllerRotationYaw = false;
}

// Called when the game starts or when sBaseed
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_BaseAnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());

	m_LockOn = false;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCharacterMovementComponent* pMovement = GetCharacterMovement();

	FVector vForward = GetActorForwardVector();
	FVector vVelocity = pMovement->Velocity;

	m_Speed = vVelocity.Size();

	if (m_Speed > 0)
	{
		//https://amored8701.tistory.com/132

		if (m_LockOn)
		{
			FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), m_LockOnBaseCharacter->GetActorLocation());

			SetActorRotation(Rotator.Quaternion());

			vForward = Rotator.RotateVector(FVector::ForwardVector);
			//
		}

		vForward.Z = 0.f;
		vVelocity.Z = 0.f;

		vForward.Normalize();
		vVelocity.Normalize();

		float fDot = FVector::DotProduct(vForward, vVelocity);
		float fAcosAngle = FMath::Acos(fDot);
		float fAngle = FMath::RadiansToDegrees(fAcosAngle);

		//if (fDot < -0.3f)
		//{
		//	m_Speed *= -1.f;
		//}

		FVector vCross = FVector::CrossProduct(vForward, vVelocity);

		if (vCross.Z < 0)
		{
			//fAngle *= -1.f;
			fAngle = 360 - fAngle;
		}

		m_Angle = fAngle;
		//PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("(%.2f, %.2f, %.2f), (%.2f, %.2f, %.2f), %.2f %.2f"), vForward.X, vForward.Y, vForward.Z, m_Angle, m_Speed));
	}

	m_BaseAnimInstance->SetSpeed(m_Speed);
	m_BaseAnimInstance->SetAngle(m_Angle);
}

float ABaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	LOG(TEXT("GetTakeDamage <%.2f>"), Damage);

	return Damage;
}

void ABaseCharacter::AddEndAnimationState(EBaseAnimType BaseCharacterAnimType)
{
	m_BaseAnimInstance->AddEndAnimationState(BaseCharacterAnimType);
}

void ABaseCharacter::SetEndAnimationState(EBaseAnimType BaseCharacterAnimType)
{
	m_BaseAnimInstance->SetEndAnimationState(BaseCharacterAnimType);
}

void ABaseCharacter::ResetAnimationState(EBaseAnimType BaseCharacterAnimType)
{
	m_BaseAnimInstance->ResetAnimationState(BaseCharacterAnimType);
}

void ABaseCharacter::SetAnimationStateEndCount(EBaseAnimType BaseCharacterAnimType, int32 Count)
{
	m_BaseAnimInstance->SetAnimationStateEndCount(BaseCharacterAnimType, Count);
}

EBaseAnimState ABaseCharacter::GetAnimationState(EBaseAnimType BaseAnimType) const
{
	return m_BaseAnimInstance->GetAnimationState(BaseAnimType);
}

void ABaseCharacter::StartAnimationState(EBaseAnimType BaseAnimType)
{
	m_BaseAnimInstance->StartAnimationState(BaseAnimType);
}

void ABaseCharacter::StartAnimationState(EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType)
{
	m_BaseAnimInstance->StartAnimationState(BaseAnimType, Direction, CombinationType);
}

void ABaseCharacter::StartAnimationState(EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType, ABaseCharacter* TargetCharacter)
{
	m_BaseAnimInstance->StartAnimationState(BaseAnimType, Direction, CombinationType, TargetCharacter);
}

void ABaseCharacter::NotifyAnimation(EAnimationNotifyType AnimationNotifyType, EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType)
{

}

EBaseAnimType ABaseCharacter::GetBaseAnimType() const
{
	return m_BaseAnimInstance->GetBaseAnimType();
}

bool ABaseCharacter::IsDeath()
{
	return false;
}

bool ABaseCharacter::IsLockOn() const
{
	return m_LockOn;
}

bool ABaseCharacter::CanMove() const
{
	EBaseAnimType BaseAnimType = m_BaseAnimInstance->GetBaseAnimType();

	if (EBaseAnimType::Idle == BaseAnimType
		|| EBaseAnimType::Walk == BaseAnimType
		|| EBaseAnimType::Run == BaseAnimType)
	{
		return true;
	}

	return false;
}

void ABaseCharacter::SetBaseAnimType(EBaseAnimType BaseAnimType)
{
	m_BaseAnimInstance->SetBaseAnimType(BaseAnimType);
}

void ABaseCharacter::SetDirection(int32 Direction)
{
	m_BaseAnimInstance->SetDirection(Direction);
}

void ABaseCharacter::SetCombinationType(ECombinationType CombinationType)
{
	m_BaseAnimInstance->SetCombinationType(CombinationType);
}

void ABaseCharacter::SetToggleWalkAndRun()
{
	if (EToggleWalkAndRun::Walk == m_ToggleWalkAndRun)
	{
		m_ToggleWalkAndRun = EToggleWalkAndRun::Run;

		GetCharacterMovement()->MaxWalkSpeed = 600;//m_PlayerVR->GetPlayerCharacterTableRow()->RunSpeed;

		if (m_Speed > 0.f)
		{
			m_BaseAnimInstance->SetBaseAnimType(EBaseAnimType::Run);
		}
	}
	else if (EToggleWalkAndRun::Run == m_ToggleWalkAndRun)
	{
		m_ToggleWalkAndRun = EToggleWalkAndRun::Walk;

		GetCharacterMovement()->MaxWalkSpeed = 100;//m_PlayerVR->GetPlayerCharacterTableRow()->WalkSpeed;

		if (m_Speed > 0.f)
		{
			m_BaseAnimInstance->SetBaseAnimType(EBaseAnimType::Walk);
		}
	}
}

void ABaseCharacter::SetTestToggle()
{
}

void ABaseCharacter::AddArmPitch(float Value)
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