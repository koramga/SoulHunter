// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "../BaseCharacter.h"

UBaseAnimInstance::UBaseAnimInstance()
{
	m_BaseAnimType = EBaseAnimType::Idle;

	m_Direction = m_InputDirection = 0;
	m_CombinationType = m_InputCombinationType = ECombinationType::None;
}

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	m_BaseAnimState = NewObject<UBaseAnimState>(this, UBaseAnimState::StaticClass());
	m_BaseAnimCombo = NewObject<UBaseAnimCombo>(this, UBaseAnimCombo::StaticClass());

	int AnimCount = static_cast<int>(GetMaxEnumValue<EBaseAnimType>());

	for (int i = 0; i < AnimCount; ++i)
	{
		m_BaseAnimState->CreateAnimationState(static_cast<EBaseAnimType>(i));
	}

	m_BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (m_InputDirection != m_Direction)
	{
		if (EBaseAnimType::Avoid != m_BaseAnimType
			&& EBaseAnimType::Attack != m_BaseAnimType
			&& EBaseAnimType::Roll != m_BaseAnimType)
		{
			m_Direction = m_InputDirection;
		}
	}

	if (m_InputCombinationType != m_CombinationType)
	{
		if (EBaseAnimType::Attack != m_BaseAnimType)
		{
			m_CombinationType = m_InputCombinationType;
		}
	}
}

void UBaseAnimInstance::AnimNotify_EnableCombo()
{
	m_BaseAnimCombo->SetEnableUpdateAnimMontage(true);
}

void UBaseAnimInstance::AnimNotify_DisableCombo()
{
	m_BaseAnimCombo->SetEnableUpdateAnimMontage(false);
}

void UBaseAnimInstance::AnimNotify_EnableCounter()
{
	m_BaseAnimCombo->SetEnableUpdateAnimMontage(true);
}

void UBaseAnimInstance::AnimNotify_DisableCounter()
{
	m_BaseAnimCombo->SetEnableUpdateAnimMontage(false);
}

void UBaseAnimInstance::AnimNotify_AttackStart()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::AttackStart, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_AttackEnd()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::AttackEnd, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_CastStart()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::CastStart, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_CastEnd()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::CastEnd, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_DefenceStart()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::DefenceStart, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_DefenceEnd()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::DefenceEnd, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_LHandStart()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::LHandStart, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_LHandEnd()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::LHandEnd , m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_RHandStart()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::RHandStart, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_RHandEnd()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::RHandEnd, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_LFootStart()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::LFootStart, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_LFootEnd()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::LFootEnd, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_RFootStart()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::RFootStart, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::AnimNotify_RFootEnd()
{
	if (IsValid(m_BaseCharacter))
	{
		m_BaseCharacter->NotifyAnimation(EAnimationNotifyType::RFootEnd, m_BaseAnimType, m_Direction, m_CombinationType);
	}
}

void UBaseAnimInstance::UpdateBaseType(EBaseAnimType BeforeBaseAnimType, EBaseAnimType AfterBaseAnimType)
{

}

void UBaseAnimInstance::UpdateSpecialAnim(UBaseAnimCombo* BaseAnimCombo, EComboType ComboType, int32 Direction, ECombinationType CombinationType)
{

}

void UBaseAnimInstance::SetBaseAnimType(EBaseAnimType BaseAnimType, bool EndAnimationStateOffset)
{
	EBaseAnimType BeforeBaseAnimType = m_BaseAnimType;

	if (EBaseAnimType::Death != BaseAnimType)
	{
		if (EndAnimationStateOffset)
		{
			m_BaseAnimType = BaseAnimType;
		}
		else
		{
			do
			{
				if (m_BaseAnimCombo->IsEnableUpdateAnimMontage())
				{
					if (EBaseAnimType::Attack == BaseAnimType)
					{
						//Combo되었다!
						m_BaseAnimCombo->UpdateAnimMontage(this);
						break;
					}
				}

				if (EBaseAnimType::Walk == BaseAnimType
					|| EBaseAnimType::Run == BaseAnimType)
				{
					if (EBaseAnimType::Idle == m_BaseAnimType
						|| EBaseAnimType::Walk == m_BaseAnimType
						|| EBaseAnimType::Run == m_BaseAnimType)

					{
						m_BaseAnimType = BaseAnimType;
					}
				}
				else if (EBaseAnimType::Idle == BaseAnimType)
				{
					if (EBaseAnimType::Walk == m_BaseAnimType
						|| EBaseAnimType::Run == m_BaseAnimType)
					{
						m_BaseAnimType = BaseAnimType;
					}
				}
				else
				{
					if (EBaseAnimType::Idle == m_BaseAnimType
						|| EBaseAnimType::Walk == m_BaseAnimType
						|| EBaseAnimType::Run == m_BaseAnimType)
					{
						m_BaseAnimType = BaseAnimType;
					}
				}
			} while (0);



		}
	}

	if (BeforeBaseAnimType != m_BaseAnimType)
	{
		UpdateBaseType(BeforeBaseAnimType, m_BaseAnimType);

		if (EBaseAnimType::Attack == m_BaseAnimType)
		{
			UpdateSpecialAnim(m_BaseAnimCombo, EComboType::Attack, m_Direction, m_CombinationType);
			m_BaseAnimCombo->StartAnimMontage(this);
		}
		else if (EBaseAnimType::Defence == m_BaseAnimType)
		{
			UpdateSpecialAnim(m_BaseAnimCombo, EComboType::Defence, m_Direction, m_CombinationType);
			m_BaseAnimCombo->StartAnimMontage(this);
		}
	}

	LOG(TEXT("AnimType <%s>"), *GetEnumerationToString(m_BaseAnimType));
}

void UBaseAnimInstance::SetEndBaseAnimType()
{
	if (EComboType::Defence == m_BaseAnimCombo->GetComboType())
	{
		m_BaseAnimCombo->EndAnimMontage(this);
	}
}

void UBaseAnimInstance::SetAngle(float Angle)
{
	m_Angle = Angle;
}

void UBaseAnimInstance::SetSpeed(float Speed)
{
	m_Speed = Speed;
}

void UBaseAnimInstance::SetDirection(int32 Direction)
{
	m_InputDirection = Direction;
}

void UBaseAnimInstance::SetCombinationType(ECombinationType CombinationType)
{
	m_InputCombinationType = CombinationType;
}

void UBaseAnimInstance::SetEnableCounter(bool EnableCounter)
{
	m_BaseAnimCombo->SetEnableUpdateAnimMontage(EnableCounter);
}

EBaseAnimType UBaseAnimInstance::GetBaseAnimType() const
{
	return m_BaseAnimType;
}

float UBaseAnimInstance::GetAngle() const
{
	return m_Angle;
}

float UBaseAnimInstance::GetSpeed() const
{
	return m_Speed;
}

int32 UBaseAnimInstance::GetDirection() const
{
	return m_InputDirection;
}

ECombinationType UBaseAnimInstance::GetCombinationType() const
{
	return m_InputCombinationType;
}

bool UBaseAnimInstance::IsEnableCounter() const
{
	return m_BaseAnimCombo->IsEnableUpdateAnimMontage();
}

void UBaseAnimInstance::AddEndAnimationState(EBaseAnimType BaseAnimType)
{
	m_BaseAnimState->AddEndAnimationState(BaseAnimType);
}

void UBaseAnimInstance::SetEndAnimationState(EBaseAnimType BaseAnimType, EBaseAnimType NextBaseAnimType)
{
	m_BaseAnimState->SetEndAnimationState(BaseAnimType);

	//끝이났으니까

	if (EComboType::None != m_BaseAnimCombo->GetComboType())
	{
		m_BaseAnimCombo->EndAnimMontage(this);
	}

	SetBaseAnimType(NextBaseAnimType, true);
}

EBaseAnimState UBaseAnimInstance::GetAnimationState(EBaseAnimType BaseAnimType)
{
	return m_BaseAnimState->GetAnimationState(BaseAnimType);
}

void UBaseAnimInstance::ResetAnimationState(EBaseAnimType BaseAnimType)
{
	m_BaseAnimState->ResetAnimationState(BaseAnimType);
}

void UBaseAnimInstance::SetAnimationStateEndCount(EBaseAnimType BaseAnimType, int32 Count)
{
	m_BaseAnimState->SetAnimationStateEndCount(BaseAnimType, Count);
}

void UBaseAnimInstance::StartAnimationState(EBaseAnimType BaseAnimType)
{
	SetBaseAnimType(BaseAnimType);

	m_BaseAnimState->SetStartAnimationState(BaseAnimType);
}

void UBaseAnimInstance::StartAnimationState(EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType)
{
	m_Direction = m_InputDirection = Direction;
	m_CombinationType = m_InputCombinationType = CombinationType;

	StartAnimationState(BaseAnimType);
}

void UBaseAnimInstance::StartAnimationState(EBaseAnimType BaseAnimType, int32 Direction, ECombinationType CombinationType, ABaseCharacter* TargetCharacter)
{
	StartAnimationState(BaseAnimType, Direction, CombinationType);

	if (IsValid(TargetCharacter)
		&& IsValid(m_BaseCharacter))
	{
		FVector ActorLocation = m_BaseCharacter->GetActorLocation();
		FVector TargetLocation = TargetCharacter->GetActorLocation();

		ActorLocation.Z = 0.f;
		TargetLocation.Z = 0.f;

		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(ActorLocation, TargetLocation);

		m_BaseCharacter->SetActorRotation(Rotator.Quaternion());
	}
}


