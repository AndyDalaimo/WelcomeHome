// Copyright Epic Games, Inc. All Rights Reserved.

#include "WelcomeHomeGameMode.h"
#include "WelcomeHomeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWelcomeHomeGameMode::AWelcomeHomeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
