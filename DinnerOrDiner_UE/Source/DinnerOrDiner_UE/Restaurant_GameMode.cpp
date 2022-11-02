// Fill out your copyright notice in the Description page of Project Settings.


#include "Restaurant_GameMode.h"
#include "Restaurant_GameState.h"
#include "Restaurant_PlayerState.h"
#include "DinnerOrDiner_UECharacter.h"
#include "UObject/ConstructorHelpers.h"

ARestaurant_GameMode::ARestaurant_GameMode()
{
	GameStateClass = ARestaurant_GameState::StaticClass();
	PlayerStateClass = ARestaurant_PlayerState::StaticClass();
	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ARestaurant_GameMode::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("Restaurant GameMode Active")));
}