// Fill out your copyright notice in the Description page of Project Settings.


#include "Bear_AIController.h"
#include "AI_Bear_char.h"
#include "AITargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"



ABear_AIController::ABear_AIController()
{
	//init bb and bt
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	//init bb keys
	LocationToGoKey = "LocationToGo";
	PlayerKey = "Target";

	CurrentTargetPoint = 0;

}

void ABear_AIController::SetPlayerCaught(APawn* Pawn_)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, Pawn_);
	}
}

void ABear_AIController::OnPossess(APawn* Pawn_)
{
	//Super::Possess(Pawn_);
	Super::OnPossess(Pawn_);
	//get ref to character
	AAI_Bear_char* AICharacter = Cast<AAI_Bear_char>(Pawn_);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}
		//populate patrol point array
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAITargetPoint::StaticClass(), PatrolPoints);

		BehaviorComp->StartTree(*AICharacter->BehaviorTree);
	}

}