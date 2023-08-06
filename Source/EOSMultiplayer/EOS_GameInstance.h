// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EOS_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class EOSMULTIPLAYER_API UEOS_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void LoginWithEOS();
	
};
