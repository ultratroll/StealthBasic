// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSPatrolGuard.generated.h"

class UPawnSensingComponent;

UCLASS()
class FPSGAME_API AFPSPatrolGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSPatrolGuard();

protected:

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensingComponent;

	FRotator OriginalRotation;

	FTimerHandle TimerReturnRotation;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** 
	*	To be called when a pawn is seen 
	*	@param PawnSeen Pawn being seen
	*/
	UFUNCTION(Category = "AI")
	void OnSeenPawn(APawn* PawnSeen);


	/**
	*	To be called when a pawn is heard
	*	@param Instigator Pawn making noise
	*	@param Location of the noise
	*	@param Volume of the noise
	*/
	UFUNCTION(Category = "AI")
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	/** Restores the guards orientation to its original one. */
	UFUNCTION(Category = "AI")
	void ResetOrientation();

public:	
	
	virtual void Tick(float DeltaTime) override;	
};
