// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFPSGameMode();

	/**
	*	On mission complete, disables input in the pawn, moves the camera to a special blueprint that serves as refrence. 
	*	@param InstigatorPawn	The pawn that completed the mission
	*	@param bMissionSuccess	The mission was a success or not
	*/
	void CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess);

	/** 
	*	On mission complete, the blueprint implementation shows the widget and does something else...
	*	@param InstigatorPawn	The pawn that completed the mission
	*	@param bMissionSuccess	The mission was a success or not
	*/
	UFUNCTION(BlueprintImplementableEvent, Category= "Mission")
	void OnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);

protected:

	UPROPERTY(EditDefaultsOnly, Category= "Spectate")
	TSubclassOf<AActor> ViewSpectatorPointClass;

};



