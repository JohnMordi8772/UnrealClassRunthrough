// Copyright Epic Games, Inc. All Rights Reserved.

#include "MedievalDungeonGameMode.h"
#include "MedievalDungeonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMedievalDungeonGameMode::AMedievalDungeonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
