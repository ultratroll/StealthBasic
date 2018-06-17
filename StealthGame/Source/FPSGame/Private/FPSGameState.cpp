// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "FPSPlayerController.h"

void AFPSGameState::MulticastOnMissionCompleted_Implementation(APawn* InstigatorCompleter, bool bMissionSuccess)
{
	// Iterate trough all pawns
// 	for (FConstPawnIterator Iterator= GetWorld()->GetPawnIterator(); Iterator; Iterator++ )
// 	{
// 		APawn* Pawn = Iterator->Get();
// 		if (Pawn && Pawn->IsLocallyControlled()) //If the Pawn being locally updated, all of them, disable input, the game ended in that machine !
// 		{
// 			Pawn->DisableInput(nullptr);
// 		}
// 	}

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; Iterator++)
	{
		AFPSPlayerController* PlayerController= Cast<AFPSPlayerController>(Iterator->Get());

		// Player controller exist twice in server and once in each client
		// The server will have additional player controllers, so we want to make sure to run it only in the local
		if (IsValid(PlayerController) && PlayerController->IsLocalController())
		{
			PlayerController->OnMissionComplete(InstigatorCompleter,bMissionSuccess);

			// We can replace the old loop commented above with this
			APawn* Pawn = PlayerController->GetPawn();
			if (Pawn && Pawn->IsLocallyControlled()) //If the Pawn being locally updated, all of them, disable input, the game ended in that machine !
			{
				Pawn->DisableInput(nullptr);
			}
		}
	}
}
