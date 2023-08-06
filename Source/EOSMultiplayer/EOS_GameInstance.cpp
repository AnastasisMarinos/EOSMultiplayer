// Fill out your copyright notice in the Description page of Project Settings.


#include "EOS_GameInstance.h"
#include  "OnlineSubsystemUtils.h"
#include "OnlineSubsystem.h"
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
