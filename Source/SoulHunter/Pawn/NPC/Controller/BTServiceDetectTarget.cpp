// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceDetectTarget.h"
#include "NPCAIController.h"
#include "../NPCCharacter.h"

UBTServiceDetectTarget::UBTServiceDetectTarget()
{
	//Interval = 0.5f;
	NodeName = TEXT("DetectTarget");
}

void UBTServiceDetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ANPCAIController* NPCAIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());

	if (nullptr == NPCAIController)
	{
		LOG(TEXT("Cast failed from AIController to NPCAIController"));
		return;
	}

	ANPCCharacter* NPCCharacter = Cast<ANPCCharacter>(NPCAIController->GetPawn());

	if (nullptr == NPCCharacter)
	{
		LOG(TEXT("Cast failed from APawn to NPCCharacter"));
		return;
	}

	if (NPCCharacter->IsDeath())
	{
		NPCAIController->SetBlackboardTargetPawnCharacter(nullptr);
		return;
	}

	float TraceRange = NPCAIController->GetBlackboardTraceRange();

	FCollisionQueryParams param(NAME_None, true, NPCCharacter);

	FVector vLoc = NPCCharacter->GetActorLocation();

	TArray<FHitResult> HitResults;

	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, vLoc, vLoc, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(TraceRange), param);

	FHitResult* HitResult = nullptr;
	float MinimumDistance = TraceRange * 2.f;

	for (FHitResult& LoopHitResult : HitResults)
	{
		APawnCharacter* PawnCharacter = Cast<APawnCharacter>(LoopHitResult.GetActor());

		if (nullptr == PawnCharacter)
		{
			continue;
		}

		if (PawnCharacter->IsDeath())
		{
			continue;
		}

		FVector vPawnLocation = PawnCharacter->GetActorLocation();

		float Distance = FVector::Distance(vPawnLocation, vLoc);

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
		NPCAIController->SetBlackboardTargetPawnCharacter(Cast<APawnCharacter>(HitResult->GetActor()));
	}
	else
	{
		NPCAIController->SetBlackboardTargetPawnCharacter(nullptr);
	}
}