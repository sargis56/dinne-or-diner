// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DINNERORDINER_UE_API SteeringOutput
{
public:

	FVector3f linear;
	float_t angular;

	SteeringOutput();
	SteeringOutput(FVector3f linear_, float_t angular_);
	inline const SteeringOutput operator + (const SteeringOutput& v) const 
	{
		return SteeringOutput(linear + v.angular, angular + v.angular);
	}
	inline SteeringOutput& operator += (const SteeringOutput& v)
	{
		linear += v.linear;
		angular += v.angular;
		return *this;
	}
	
};
