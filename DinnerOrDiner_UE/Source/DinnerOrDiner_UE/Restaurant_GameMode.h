// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Restaurant_GameMode.generated.h"

UCLASS()
class DINNERORDINER_UE_API ARestaurant_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARestaurant_GameMode();
	
protected:
	virtual void BeginPlay() override;
};