// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Restaurant_GameState.generated.h"

UCLASS()
class DINNERORDINER_UE_API ARestaurant_GameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ARestaurant_GameState();
	
protected:
	virtual void BeginPlay() override;
};