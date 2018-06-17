// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"




void AFPSGameState::MulticastOnMissionCompleted_Implementation(APawn* InstigatorCompleter, bool bMissionSuccess)
{
	// Iterate trough all pawns
	for (FConstPawnIterator Iterator= GetWorld()->GetPawnIterator(); Iterator; Iterator++ )
	{
		APawn* Pawn = Iterator->Get();
		if (Pawn && Pawn->IsLocallyControlled()) //If the Pawn being locally updated, all of them, disable input, the game ended in that machine !
		{
			Pawn->DisableInput(nullptr);
		}
	}
}
