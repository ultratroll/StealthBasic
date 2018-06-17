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
		if (ViewSpectatorPointClass)
		{
			TArray<AActor*> ViewPointActors;
			UGameplayStatics::GetAllActorsOfClass(this, ViewSpectatorPointClass, ViewPointActors);

			if (ViewPointActors.Num() > 0)
			{
				AActor* NewViewTarget = ViewPointActors[0];

				for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; Iterator++)
				{
					APlayerController* PlayerController = Iterator->Get();

					if (PlayerController) // This is called in the server (gamemode only exist in the server), no need to check if its locally
					{
						PlayerController->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic); // SetViewTargetWithBlend replicates, so when the GM calls it in all player controllers, it actually gets called on all machines
					}
				}
			}
		}
	}

	AFPSGameState* GameState = GetGameState<AFPSGameState>();
	if (IsValid(GameState))
	{
		GameState->MulticastOnMissionCompleted(InstigatorPawn, bMissionSuccess);
	}
}

