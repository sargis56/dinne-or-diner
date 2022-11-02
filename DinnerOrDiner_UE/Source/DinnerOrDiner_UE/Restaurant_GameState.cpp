// Fill out your copyright notice in the Description page of Project Settings.


#include "Restaurant_GameState.h"
#include "Engine/Engine.h"

ARestaurant_GameState::ARestaurant_GameState()
{

}

void ARestaurant_GameState::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.5f, FColor::Emerald, FString::Printf(TEXT("Restaurant GameState Active")));
}