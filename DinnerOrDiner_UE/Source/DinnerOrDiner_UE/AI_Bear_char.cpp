// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Bear_char.h"
#include "Components/CapsuleComponent.h"
#include "Bear_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AAI_Bear_char::AAI_Bear_char()
{
 	//init senses
	PawnSenseComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSenseComp->SetPeripheralVisionAngle(90.0f);

}

// Called when the game starts or when spawned
void AAI_Bear_char::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSenseComp)
	{
		PawnSenseComp->OnSeePawn.AddDynamic(this, &AAI_Bear_char::OnPlayerCaught);
	}
	
}

// Called every frame
void AAI_Bear_char::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAI_Bear_char::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAI_Bear_char::OnPlayerCaught(APawn* Pawn)
{
	//get ref to player controller
	ABear_AIController* AIController = Cast<ABear_AIController>(GetController());

	if (AIController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You've been caught!"));
		AIController->SetPlayerCaught(Pawn);
	}

}

