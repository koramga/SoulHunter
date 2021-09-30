// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceDetectTarget.h"
#include "../BaseAIController.h"
#include "../../../Character/BaseCharacter.h"

UBTServiceDetectTarget::UBTServiceDetectTarget()
{
	//Interval = 0.5f;
	NodeName = TEXT("DetectTarget");
}

void UBTServiceDetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ABaseAIController* BaseAIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());

	if (nullptr == BaseAIController)
	{
		LOG(TEXT("Cast failed from AIController to BaseAIController"));
		return;
	}

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(BaseAIController->GetPawn());

	if (nullptr == BaseCharacter)
	{
		LOG(TEXT("Cast failed from ABase to BaseCharacter"));
		return;
	}

	if (BaseCharacter->IsDeath())
	{
		BaseAIController->SetBlackboardTargetCharacter(nullptr);
		return;
	}

	float TraceRange = BaseAIController->GetBlackboardTraceRange();

	FCollisionQueryParams param(NAME_None, true, BaseCharacter);

	FVector vLoc = BaseCharacter->GetActorLocation();

	TArray<FHitResult> HitResults;

	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, vLoc, vLoc, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(TraceRange), param);

	FHitResult* HitResult = nullptr;
	float MinimumDistance = TraceRange * 2.f;

	for (FHitResult& LoopHitResult : HitResults)
	{
		ABaseCharacter* LoopBaseCharacter = Cast<ABaseCharacter>(LoopHitResult.GetActor());

		if (nullptr == LoopBaseCharacter)
		{
			continue;
		}

		if (LoopBaseCharacter->IsDeath())
		{
			continue;
		}

		FVector vLoopLocation = LoopBaseCharacter->GetActorLocation();

		float Distance = FVector::Distance(vLoopLocation, vLoc);

		if (MinimumDistance <= Distance)
		{
			//������ ������ ����. (�ִܰŸ��� ã�Ƽ� �����ϰ� �����.)
			continue;
		}

		MinimumDistance = Distance;

		HitResult = &LoopHitResult;
	}

#if ENABLE_DRAW_DEBUG

	FColor DrawColor = HitResult ? FColor::Red : FColor::Green;
	FQuat	qut = FQuat::Identity;

	DrawDebugSphere(GetWorld(), vLoc, TraceRange, 20, DrawColor, false, 0.5f);

	//DrawDebugCapsule(GetWorld(), vLoc + vForward * 200 / 2.f, 200 / 2.f + 50.f, 50.f
	//	, qut, DrawColor, false, 2.f);

#endif

		//�浹�� �Ǿ��ٸ� �������� Target�� �浹�� ��ü�� �������ش�.
		//�ƴ϶�� nullptr�� �����Ѵ�.
	if (nullptr != HitResult)
	{
		//Ư���� �˰����� ���ؼ� �ټ��� Target�� �߰ߵǾ��� �� ��� ���� �����ؾ��Ѵ�.
		BaseAIController->SetBlackboardTargetCharacter(Cast<ABaseCharacter>(HitResult->GetActor()));
	}
	else
	{
		BaseAIController->SetBlackboardTargetCharacter(nullptr);
	}
}