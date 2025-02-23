// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EOSMultiplayerGameMode.generated.h"

UCLASS(minimalapi)
class AEOSMultiplayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEOSMultiplayerGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};



