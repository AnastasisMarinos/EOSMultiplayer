// Fill out your copyright notice in the Description page of Project Settings.


#include "EOS_GameInstance.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineIdentityInterface.h"

void UEOS_GameInstance::LoginWithEOS(FString ID, FString Token, FString LoginType)
{
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if(SubsystemRef)
	{
		IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
		if(IdentityPointerRef)
		{
			FOnlineAccountCredentials AccountCredentials;
			AccountCredentials.Id = ID;
			AccountCredentials.Token = Token;
			AccountCredentials.Type = LoginType;
			IdentityPointerRef->OnLoginCompleteDelegates->AddUObject(this, &UEOS_GameInstance::LoginWithEOS_Return);
			IdentityPointerRef->Login(0, AccountCredentials);
		}
	}
}

FString UEOS_GameInstance::GetPlayerUsername()
{
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if(SubsystemRef)
	{
		IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
		if(IdentityPointerRef)
		{
			if(IdentityPointerRef->GetLoginStatus(0) == ELoginStatus::LoggedIn)
			{
				return IdentityPointerRef->GetPlayerNickname(0);
			}
		}
	}
	return FString();
}

bool UEOS_GameInstance::IsPlayerLoggedIn()
{
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if(SubsystemRef)
	{
		IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
		if(IdentityPointerRef)
		{
			if(IdentityPointerRef->GetLoginStatus(0) == ELoginStatus::LoggedIn)
			{
				return true;
			}
		}
	}
	return false;
}

void UEOS_GameInstance::LoginWithEOS_Return(int32 LocalUserNum, bool bWasSuccess, const FUniqueNetId& UserID, const FString& ErrorMessage)
{
	if(bWasSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("LOGIN SUCCESS"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("LOGIN ERROR - %s"), *ErrorMessage);
	}
}

// CREATE SESSION //

void UEOS_GameInstance::CreateEOSSession(bool bIsDedicatedServer, bool bIsLANServer, int32 NumOfPublicConnections)
{
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if(SubsystemRef)
	{
		IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface();
		if(SessionPtrRef)
		{
			FOnlineSessionSettings SessionCreationSettings;
			SessionCreationSettings.bIsDedicated = bIsDedicatedServer;
			SessionCreationSettings.bAllowInvites = true;
			SessionCreationSettings.bIsLANMatch = bIsLANServer;
			SessionCreationSettings.NumPublicConnections = NumOfPublicConnections;
			SessionCreationSettings.bUseLobbiesIfAvailable = false;
			SessionCreationSettings.bUsesPresence = false;
			SessionCreationSettings.bShouldAdvertise = true;
			SessionCreationSettings.Set(SEARCH_KEYWORDS, FString("RandomHi"), EOnlineDataAdvertisementType::ViaOnlineService);
			SessionPtrRef->OnCreateSessionCompleteDelegates.AddUObject(this, &UEOS_GameInstance::OnCreateSessionCompleted);
			SessionPtrRef->CreateSession(0, FName("MainSession"), SessionCreationSettings);
		}
	}
}

void UEOS_GameInstance::OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful)
{
	if(bWasSuccessful)
	{
		GetWorld()->ServerTravel(OpenLevelText);
	}
}

// FIND SESSION

void UEOS_GameInstance::FindSessionAndJoin()
{
	
}

void UEOS_GameInstance::OnFindSessionCompleted(bool bWasSuccesful)
{
	
}

// JOIN SESSION //

void UEOS_GameInstance::JoinSession()
{
	
}

void UEOS_GameInstance::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	
}

