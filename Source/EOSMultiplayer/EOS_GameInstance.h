// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "EOS_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class EOSMULTIPLAYER_API UEOS_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void LoginWithEOS(FString ID, FString Token, FString LoginType);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="EOS Functions")
	FString GetPlayerUsername();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="EOS Functions")
	bool IsPlayerLoggedIn();

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void CreateEOSSession(bool bIsDedicatedServer, bool bIsLANServer, int32 NumOfPublicConnections);

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void FindSessionAndJoin();

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void JoinSession();

	//TSharedRef<FOnlineSessionSearch> SessionSearch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EOS Variables")
	FString OpenLevelText;

	
	void LoginWithEOS_Return(int32 LocalUserNum, bool bWasSuccess, const FUniqueNetId& UserID, const FString& ErrorMessage);
	void OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful);
	void OnFindSessionCompleted(bool bWasSuccesful);
	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
