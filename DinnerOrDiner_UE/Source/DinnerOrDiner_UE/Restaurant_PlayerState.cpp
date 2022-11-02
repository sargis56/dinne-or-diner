// Fill out your copyright notice in the Description page of Project Settings.


#include "Restaurant_PlayerState.h"
#include "Engine/Engine.h"

ARestaurant_PlayerState::ARestaurant_PlayerState()
{

}

void ARestaurant_PlayerState::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 7.5f, FColor::Emerald, FString::Printf(TEXT("Restaurant PlayerState Active")));
}