// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSPatrolGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EGUARD_AI_STATE : uint8
{
	Idle,
	Suspicious,
	Alerted
};


UCLASS()
class FPSGAME_API AFPSPatrolGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSPatrolGuard();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = AI)
	void SetGuardState(const EGUARD_AI_STATE &NewGuardState);

	UFUNCTION(BlueprintCallable, Category = AI)
	const EGUARD_AI_STATE &GetGuardState() { return GuardState; }

	UFUNCTION(BlueprintImplementableEvent, Category = AI)
	void OnGuardStateChanged(const EGUARD_AI_STATE &NewGuardState);

protected:

	UPROPERTY(EditInstanceOnly, Category= "AI")
	uint8 bPatrol: 1;

	UPROPERTY(Transient)
	uint8 CurrentPatrolPointIdx : 1;

	UPROPERTY(EditInstanceOnly, Category = "AI")
	float MinimalDistance = 100.0f;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition="bPatrol"))
	TArray <AActor*> PatrolPoints;

	UPROPERTY(Transient)
	AActor* CurrentPatrolPoint;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(Transient)
	FRotator OriginalRotation;

	UPROPERTY(Transient)
	FTimerHandle TimerReturnRotation;

	/** Current state of the guard. */
	UPROPERTY(Transient)
	EGUARD_AI_STATE GuardState;

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

	/** Moves to the next patrol point. */
	UFUNCTION(Category = "AI")
	void MoveNextPatrolPoint();

};
