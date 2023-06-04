// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheRizzardGameMode.h"
#include "TheRizzardCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheRizzardGameMode::ATheRizzardGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
