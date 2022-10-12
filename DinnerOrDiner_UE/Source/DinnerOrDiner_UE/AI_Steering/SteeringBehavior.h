// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SteeringOutput.h"
#include "GameFramework/Character.h"

/**
 * 
 */
class DINNERORDINER_UE_API SteeringBehavior
{
protected:

	enum class SteeringOutputs
	{
		Kinematic = 0,
		Dynamic
	};

	SteeringOutput* result;
	ACharacter* character;


public:
	SteeringBehavior();
	~SteeringBehavior()
	{
		if (result) delete result;
	}
};
