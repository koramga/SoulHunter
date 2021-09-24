// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "BaseAnimCombo.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UBaseAnimCombo : public UObject
{
	GENERATED_BODY()

public:
	UBaseAnimCombo();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UAnimMontage* m_AnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	bool				m_EnableUpdateMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EComboType			m_ComboType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	int32				m_AnimMontageSectionIndex;

public:
	static FName GetComboStartName(int32 ComboIndex);
	static FName GetComboEndeName(int32 ComboIndex);

public:
	void SetAnimMontage(UAnimMontage* AnimMontage, EComboType ComboType = EComboType::Attack);
	void StartAnimMontage(UAnimInstance* AnimInstance);
	void UpdateAnimMontage(UAnimInstance* AnimInstance);
	void EndAnimMontage(UAnimInstance* AnimInstance);

public:
	void SetEnableUpdateAnimMontage(bool EnableUpdateAnimMontage);

public:
	bool IsEnableUpdateAnimMontage() const;
	EComboType GetComboType() const;
	
};
