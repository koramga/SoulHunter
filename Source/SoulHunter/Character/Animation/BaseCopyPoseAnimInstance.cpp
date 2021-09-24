// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCopyPoseAnimInstance.h"

void UBaseCopyPoseAnimInstance::SetSrcSkeletalMeshComponent(USkeletalMeshComponent* SrcMeshComponent)
{
	m_SrcMeshComponent = SrcMeshComponent;
}

USkeletalMeshComponent* UBaseCopyPoseAnimInstance::GetSrcSkeletalMeshComponent() const
{
	return m_SrcMeshComponent;
}

