// Copyright Epic Games, Inc. All Rights Reserved.

#include "EOSMultiplayerGameMode.h"
#include "EOSMultiplayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEOSMultiplayerGameMode::AEOSMultiplayerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
