// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAnimInstance.h"
#include "../PawnCharacter.h"

UPawnAnimInstance::UPawnAnimInstance()
{
	m_PawnAnimType = EPawnAnimType::Idle;

	m_Direction = m_InputDirection = 0;
	m_CombinationType = m_InputCombinationType = ECombinationType::None;
}

void UPawnAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	m_PawnAnimState = NewObject<UPawnAnimState>(this, UPawnAnimState::StaticClass());
	m_PawnAnimCombo = NewObject<UPawnAnimCombo>(this, UPawnAnimCombo::StaticClass());

	for (int i = 0; i < static_cast<int>(EPawnAnimType::Max); ++i)
	{
		m_PawnAnimState->CreateAnimationState(static_cast<EPawnAnimType>(i));
	}

	m_PawnCharacter = Cast<APawnCharacter>(TryGetPawnOwner());
}

void UPawnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (m_InputDirection != m_Direction)
	{
		if (EPawnAnimType::Avoid != m_PawnAnimType
			&& EPawnAnimType::Attack != m_PawnAnimType
			&& EPawnAnimType::Roll != m_PawnAnimType)
		{
			m_Direction = m_InputDirection;
		}
	}

	if (m_InputCombinationType != m_CombinationType)
	{
		if (EPawnAnimType::Attack != m_PawnAnimType)
		{
			m_CombinationType = m_InputCombinationType;
		}
	}
}

void UPawnAnimInstance::AnimNotify_EnableCombo()
{
	m_PawnAnimCombo->SetEnableUpdateAnimMontage(true);
}

void UPawnAnimInstance::AnimNotify_DisableCombo()
{
	m_PawnAnimCombo->SetEnableUpdateAnimMontage(false);
}

void UPawnAnimInstance::AnimNotify_EnableCounter()
{
	m_PawnAnimCombo->SetEnableUpdateAnimMontage(true);
}

void UPawnAnimInstance::AnimNotify_DisableCounter()
{
	m_PawnAnimCombo->SetEnableUpdateAnimMontage(false);
}

void UPawnAnimInstance::AnimNotify_AttackStart()
{
	if (IsValid(m_PawnCharacter))
	{
		m_PawnCharacter->NotifyAnimation(EAnimationNotifyType::AttackStart, m_PawnAnimType, m_Direction, m_CombinationType);
	}
}

void UPawnAnimInstance::AnimNotify_AttackEnd()
{
	if (IsValid(m_PawnCharacter))
	{
		m_PawnCharacter->NotifyAnimation(EAnimationNotifyType::AttackEnd, m_PawnAnimType, m_Direction, m_CombinationType);
	}
}

void UPawnAnimInstance::AnimNotify_CastStart()
{
	if (IsValid(m_PawnCharacter))
	{
		m_PawnCharacter->NotifyAnimation(EAnimationNotifyType::CastStart, m_PawnAnimType, m_Direction, m_CombinationType);
	}
}

void UPawnAnimInstance::AnimNotify_CastEnd()
{
	if (IsValid(m_PawnCharacter))
	{
		m_PawnCharacter->NotifyAnimation(EAnimationNotifyType::CastEnd, m_PawnAnimType, m_Direction, m_CombinationType);
	}
}

void UPawnAnimInstance::AnimNotify_DefenceStart()
{
	if (IsValid(m_PawnCharacter))
	{
		m_PawnCharacter->NotifyAnimation(EAnimationNotifyType::DefenceStart, m_PawnAnimType, m_Direction, m_CombinationType);
	}
}

void UPawnAnimInstance::AnimNotify_DefenceEnd()
{
	if (IsValid(m_PawnCharacter))
	{
		m_PawnCharacter->NotifyAnimation(EAnimationNotifyType::DefenceEnd, m_PawnAnimType, m_Direction, m_CombinationType);
	}
}

void UPawnAnimInstance::UpdatePawnType(EPawnAnimType BeforePawnAnimType, EPawnAnimType AfterPawnAnimType)
{

}

void UPawnAnimInstance::UpdateSpecialAnim(UPawnAnimCombo* PawnAnimCombo, EComboType ComboType, int32 Direction, ECombinationType CombinationType)
{

}

void UPawnAnimInstance::SetPawnAnimType(EPawnAnimType PawnAnimType, bool EndAnimationStateOffset)
{
	EPawnAnimType BeforePawnAnimType = m_PawnAnimType;

	if (EPawnAnimType::Death != PawnAnimType)
	{
		if (EndAnimationStateOffset)
		{
			m_PawnAnimType = PawnAnimType;
		}
		else
		{
			do
			{
				if (m_PawnAnimCombo->IsEnableUpdateAnimMontage())
				{
					if (EPawnAnimType::Attack == PawnAnimType)
					{
						//Combo되었다!
						m_PawnAnimCombo->UpdateAnimMontage(this);
						break;
					}
				}

				if (EPawnAnimType::Idle == PawnAnimType)
				{
					if (EComboType::Defence == m_PawnAnimCombo->GetComboType())
					{
						//이러면 이제 끝내야한다는 신호로 받아들인다.
						m_PawnAnimCombo->EndAnimMontage(this);
						break;
					}
				}

				if (EPawnAnimType::Walk == PawnAnimType
					|| EPawnAnimType::Run == PawnAnimType)
				{
					if (EPawnAnimType::Idle == m_PawnAnimType
						|| EPawnAnimType::Walk == m_PawnAnimType
						|| EPawnAnimType::Run == m_PawnAnimType)

					{
						m_PawnAnimType = PawnAnimType;
					}
				}
				else if (EPawnAnimType::Idle == PawnAnimType)
				{
					if (EPawnAnimType::Walk == m_PawnAnimType
						|| EPawnAnimType::Run == m_PawnAnimType)
					{
						m_PawnAnimType = PawnAnimType;
					}
				}
				else
				{
					if (EPawnAnimType::Idle == m_PawnAnimType
						|| EPawnAnimType::Walk == m_PawnAnimType
						|| EPawnAnimType::Run == m_PawnAnimType)
					{
						m_PawnAnimType = PawnAnimType;
					}
				}
			} while (0);



		}
	}

	if (BeforePawnAnimType != m_PawnAnimType)
	{
		UpdatePawnType(BeforePawnAnimType, m_PawnAnimType);

		if (EPawnAnimType::Attack == m_PawnAnimType)
		{
			UpdateSpecialAnim(m_PawnAnimCombo, EComboType::Attack, m_Direction, m_CombinationType);
			m_PawnAnimCombo->StartAnimMontage(this);
		}
		else if (EPawnAnimType::Defence == m_PawnAnimType)
		{
			UpdateSpecialAnim(m_PawnAnimCombo, EComboType::Defence , m_Direction, m_CombinationType);
			m_PawnAnimCombo->StartAnimMontage(this);
		}
	}
}

void UPawnAnimInstance::SetAngle(float Angle)
{
	m_Angle = Angle;
}

void UPawnAnimInstance::SetSpeed(float Speed)
{
	m_Speed = Speed;
}

void UPawnAnimInstance::SetDirection(int32 Direction)
{
	m_InputDirection = Direction;
}

void UPawnAnimInstance::SetCombinationType(ECombinationType CombinationType)
{
	m_InputCombinationType = CombinationType;
}

void UPawnAnimInstance::SetEnableCounter(bool EnableCounter)
{
	m_PawnAnimCombo->SetEnableUpdateAnimMontage(EnableCounter);
}

EPawnAnimType UPawnAnimInstance::GetPawnAnimType() const
{
	return m_PawnAnimType;
}

float UPawnAnimInstance::GetAngle() const
{
	return m_Angle;
}

float UPawnAnimInstance::GetSpeed() const
{
	return m_Speed;
}

int32 UPawnAnimInstance::GetDirection() const
{
	return m_InputDirection;
}

ECombinationType UPawnAnimInstance::GetCombinationType() const
{
	return m_InputCombinationType;
}

void UPawnAnimInstance::AddEndAnimationState(EPawnAnimType PawnAnimType)
{
	m_PawnAnimState->AddEndAnimationState(PawnAnimType);
}

void UPawnAnimInstance::SetEndAnimationState(EPawnAnimType PawnAnimType, EPawnAnimType NextPawnAnimType)
{
	m_PawnAnimState->SetEndAnimationState(PawnAnimType);

	//끝이났으니까

	SetPawnAnimType(NextPawnAnimType, true);
}

EPawnAnimState UPawnAnimInstance::GetAnimationState(EPawnAnimType PawnAnimType)
{
	return m_PawnAnimState->GetAnimationState(PawnAnimType);
}

void UPawnAnimInstance::ResetAnimationState(EPawnAnimType PawnAnimType)
{
	m_PawnAnimState->ResetAnimationState(PawnAnimType);
}

void UPawnAnimInstance::SetAnimationStateEndCount(EPawnAnimType PawnAnimType, int32 Count)
{
	m_PawnAnimState->SetAnimationStateEndCount(PawnAnimType, Count);
}

void UPawnAnimInstance::StartAnimationState(EPawnAnimType PawnAnimType)
{
	SetPawnAnimType(PawnAnimType);

	m_PawnAnimState->SetStartAnimationState(PawnAnimType);
}

void UPawnAnimInstance::StartAnimationState(EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType)
{
	m_Direction = m_InputDirection = Direction;
	m_CombinationType = m_InputCombinationType = CombinationType;

	StartAnimationState(PawnAnimType);
}

void UPawnAnimInstance::StartAnimationState(EPawnAnimType PawnAnimType, int32 Direction, ECombinationType CombinationType, APawnCharacter* TargetCharacter)
{
	StartAnimationState(PawnAnimType, Direction, CombinationType);

	if (IsValid(TargetCharacter)
		&& IsValid(m_PawnCharacter))
	{
		FVector ActorLocation = m_PawnCharacter->GetActorLocation();
		FVector TargetLocation = TargetCharacter->GetActorLocation();

		ActorLocation.Z = 0.f;
		TargetLocation.Z = 0.f;

		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(ActorLocation, TargetLocation);

		m_PawnCharacter->SetActorRotation(Rotator.Quaternion());
	}
}
