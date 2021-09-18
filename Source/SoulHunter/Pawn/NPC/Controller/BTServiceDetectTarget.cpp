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
			//변경할 이유가 없다. (최단거리를 찾아서 공격하게 만든다.)
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

		//충돌이 되었다면 블랙보드의 Target에 충돌된 객체를 지정해준다.
		//아니라면 nullptr를 지정한다.
	if (nullptr != HitResult)
	{
		//특정한 알고리즘을 통해서 다수의 Target이 발견되었을 때 어떻게 할지 정의해야한다.
		NPCAIController->SetBlackboardTargetPawnCharacter(Cast<APawnCharacter>(HitResult->GetActor()));
	}
	else
	{
		NPCAIController->SetBlackboardTargetPawnCharacter(nullptr);
	}
}