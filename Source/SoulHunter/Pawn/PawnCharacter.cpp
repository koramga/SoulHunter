// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnCharacter.h"
#include "Animation/PawnAnimInstance.h"
// Sets default values
APawnCharacter::APawnCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APawnCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_PawnAnimInstance = Cast<UPawnAnimInstance>(GetMesh()->GetAnimInstance());

	m_LookAtMode = false;
}

// Called every frame
void APawnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCharacterMovementComponent* pMovement = GetCharacterMovement();

	FVector vForward = GetActorForwardVector();
	FVector vVelocity = pMovement->Velocity;

	m_Speed = vVelocity.Size();

	if (m_Speed > 0)
	{
		//https://amored8701.tistory.com/132

		if (m_LookAtMode)
		{
			FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), m_LookAtPawnCharacter->GetActorLocation());

			LOG(TEXT("Rotator : <%.2f, %.2f, %.2f>"), Rotator.Pitch, Rotator.Yaw, Rotator.Roll);

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

	m_PawnAnimInstance->SetSpeed(m_Speed);
	m_PawnAnimInstance->SetAngle(m_Angle);
}

EPawnAnimType APawnCharacter::GetPawnAnimType() const
{
	return m_PawnAnimInstance->GetPawnAnimType();
}

void APawnCharacter::AddEndAnimationState(EPawnAnimType PawnCharacterAnimType)
{
	m_PawnAnimInstance->AddEndAnimationState(PawnCharacterAnimType);
}

void APawnCharacter::SetEndAnimationState(EPawnAnimType PawnCharacterAnimType)
{
	m_PawnAnimInstance->SetEndAnimationState(PawnCharacterAnimType);
}

void APawnCharacter::ResetAnimationState(EPawnAnimType PawnCharacterAnimType)
{
	m_PawnAnimInstance->ResetAnimationState(PawnCharacterAnimType);
}

void APawnCharacter::SetAnimationStateEndCount(EPawnAnimType PawnCharacterAnimType, int32 Count)
{
	m_PawnAnimInstance->SetAnimationStateEndCount(PawnCharacterAnimType, Count);
}

EPawnAnimState APawnCharacter::GetAnimationState(EPawnAnimType PawnAnimType) const
{
	return m_PawnAnimInstance->GetAnimationState(PawnAnimType);
}

void APawnCharacter::StartAnimationState(EPawnAnimType PawnAnimType)
{
	m_PawnAnimInstance->StartAnimationState(PawnAnimType);
}

void APawnCharacter::StartAnimationState(EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType)
{
	m_PawnAnimInstance->StartAnimationState(PawnAnimType, Direction, CombinationType);
}

void APawnCharacter::StartAnimationState(EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType, APawnCharacter* TargetCharacter)
{
	m_PawnAnimInstance->StartAnimationState(PawnAnimType, Direction, CombinationType, TargetCharacter);
}

bool APawnCharacter::IsDeath()
{
	return false;
}