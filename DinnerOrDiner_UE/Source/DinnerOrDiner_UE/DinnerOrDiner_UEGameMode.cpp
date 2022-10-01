// Copyright Epic Games, Inc. All Rights Reserved.

#include "DinnerOrDiner_UEGameMode.h"
#include "DinnerOrDiner_UECharacter.h"
#include "UObject/ConstructorHelpers.h"

ADinnerOrDiner_UEGameMode::ADinnerOrDiner_UEGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
