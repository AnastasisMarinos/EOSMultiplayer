// Copyright Epic Games, Inc. All Rights Reserved.

#include "EOSMultiplayerGameMode.h"
#include "EOSMultiplayerCharacter.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
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

void AEOSMultiplayerGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if(NewPlayer)
	{
		FUniqueNetIdRepl UniqueNetIdRepl;
		if(NewPlayer->IsLocalController())
		{
			ULocalPlayer *LocalPlayerRef = NewPlayer->GetLocalPlayer();
			if(LocalPlayerRef)
			{
				UniqueNetIdRepl = LocalPlayerRef->GetPreferredUniqueNetId();
			}
			else
			{
				UNetConnection *RemoteNetConnectionRef = Cast<UNetConnection>(NewPlayer->Player);
				check(IsValid(RemoteNetConnectionRef));
				UniqueNetIdRepl = RemoteNetConnectionRef->PlayerId;
			}
		}
		else
		{
			TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
			check(UniqueNetId != nullptr)
			IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(NewPlayer->GetWorld());
			IOnlineSessionPtr SessionRef = SubsystemRef->GetSessionInterface();
			bool bRegistrationSuccess = SessionRef->RegisterPlayer(FName("MainSession"), *UniqueNetId, false);
			if(bRegistrationSuccess)
			{
				UE_LOG(LogTemp, Warning, TEXT("REGISTRATION SUCCESSFUL"));
			}
		}
	}
}
