// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringOutput.h"

SteeringOutput::SteeringOutput()
{
	linear = FVector3f(0.0f, 0.0f, 0.0f);
	angular = 0.0f;
}

SteeringOutput::SteeringOutput(FVector3f linear_, float_t angular_)
{
	linear = linear_;
	angular = angular_;
}


