// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_AndroidGameMode.h"
#include "FPS_AndroidCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPS_AndroidGameMode::AFPS_AndroidGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
