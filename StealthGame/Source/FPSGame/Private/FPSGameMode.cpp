// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		//InstigatorPawn->DisableInput(nullptr);  // We want this to happen on all clients, will pass it to gamemode	

		if (ViewSpectatorPointClass)
		{
			TArray<AActor*> ViewPointActors;
			UGameplayStatics::GetAllActorsOfClass(this, ViewSpectatorPointClass, ViewPointActors);

			if (ViewPointActors.Num() > 0)
			{
				if (APlayerController* PlayerController = Cast<APlayerController>(InstigatorPawn->GetController()))
				{
					AActor* NewViewTarget = ViewPointActors[0];
					PlayerController->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
	}

	AFPSGameState* GameState = GetGameState<AFPSGameState>();
	if (IsValid(GameState))
	{
		GameState->MulticastOnMissionCompleted(InstigatorPawn, bMissionSuccess);
	}

	//OnMissionCompleted(InstigatorPawn, bMissionSuccess); // We want this to happen on all clients
}

