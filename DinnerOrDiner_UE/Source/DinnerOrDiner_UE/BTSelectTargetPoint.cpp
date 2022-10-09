// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSelectTargetPoint.h"
#include "AITargetPoint.h"
#include "Bear_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSelectTargetPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABear_AIController* AICon = Cast<ABear_AIController>(OwnerComp.GetAIOwner());
	if (AICon)
	{
		//get bb comp
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();

		AAITargetPoint* currentPoint = Cast<AAITargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailableTargetPoints = AICon->GetPartolPoints();

		AAITargetPoint* nextPoint = nullptr;

		if (AICon->CurrentTargetPoint != AvailableTargetPoints.Num() - 1)
		{
			nextPoint = Cast<AAITargetPoint>(AvailableTargetPoints[++AICon->CurrentTargetPoint]);
		}
		else // if there is no more points to go to
		{
			nextPoint = Cast<AAITargetPoint>(AvailableTargetPoints[0]);
			AICon->CurrentTargetPoint = 0;
		}
		BlackboardComp->SetValueAsObject("LocationToGo", nextPoint);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
