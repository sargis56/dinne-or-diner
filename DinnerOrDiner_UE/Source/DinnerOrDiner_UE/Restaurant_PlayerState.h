// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Restaurant_PlayerState.generated.h"

UCLASS()
class DINNERORDINER_UE_API ARestaurant_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ARestaurant_PlayerState();
	
protected:
	virtual void BeginPlay() override;
};