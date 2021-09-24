// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "BaseCopyPoseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULHUNTER_API UBaseCopyPoseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	USkeletalMeshComponent* m_SrcMeshComponent;

public:
	void SetSrcSkeletalMeshComponent(USkeletalMeshComponent* SrcMeshComponent);
	USkeletalMeshComponent* GetSrcSkeletalMeshComponent() const;
	
};
