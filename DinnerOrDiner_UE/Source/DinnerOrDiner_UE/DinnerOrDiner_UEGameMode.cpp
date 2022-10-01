// Copyright Epic Games, Inc. All Rights Reserved.

#include "DinnerOrDiner_UEGameMode.h"
#include "DinnerOrDiner_UECharacter.h"
#include "UObject/ConstructorHelpers.h"

ADinnerOrDiner_UEGameMode::ADinnerOrDiner_UEGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
