// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	/** Used to help disable input and show mission ending UI on all clients. */
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnMissionCompleted(APawn* InstigatorCompleter, bool bMissionSuccess);
	
};