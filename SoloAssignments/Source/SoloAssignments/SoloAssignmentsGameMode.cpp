// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoloAssignmentsGameMode.h"
#include "SoloAssignmentsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASoloAssignmentsGameMode::ASoloAssignmentsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
