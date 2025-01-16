// Copyright Epic Games, Inc. All Rights Reserved.

#include "SiriusGameMode.h"
#include "SiriusCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASiriusGameMode::ASiriusGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
