// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPatrolGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSPatrolGuard::AFPSPatrolGuard()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AFPSPatrolGuard::OnSeenPawn);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AFPSPatrolGuard::OnNoiseHeard);

	GuardState = EGUARD_AI_STATE::Idle;
}

void AFPSPatrolGuard::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalRotation = GetActorRotation();
}

void AFPSPatrolGuard::OnSeenPawn(APawn* PawnSeen)
{
	if (!IsValid(PawnSeen))
		return;

	DrawDebugLine(GetWorld(), this->GetActorLocation(), PawnSeen->GetActorLocation(), FColor::Red, false, 0.5f);

	DrawDebugSphere(GetWorld(), PawnSeen->GetActorLocation(), 32, 12, FColor::Red, false, 5.0f);

	// lose game
	AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		SetGuardState(EGUARD_AI_STATE::Alerted);
		GameMode->CompleteMission(PawnSeen, false);
	}
}

void AFPSPatrolGuard::OnNoiseHeard(APawn * NoiseInstigator, const FVector & Location, float Volume)
{
	if (GuardState == EGUARD_AI_STATE::Alerted)
		return;

	DrawDebugLine(GetWorld(), this->GetActorLocation(), Location, FColor::Blue, false, 0.5f);
	DrawDebugSphere(GetWorld(), Location, 32, 12, FColor::Blue, false, 5.0f);

	FVector DirectionOfNoise = Location - this->GetActorLocation();
	DirectionOfNoise.Normalize();

	FRotator LookAt= FRotationMatrix::MakeFromX(DirectionOfNoise).Rotator();

	LookAt.Pitch = 0.0f;
	LookAt.Roll = 0.0f;

	SetActorRotation(LookAt);

	GetWorldTimerManager().ClearTimer(TimerReturnRotation);
	GetWorldTimerManager().SetTimer(TimerReturnRotation, this, &AFPSPatrolGuard::ResetOrientation, 3.0f);

	SetGuardState(EGUARD_AI_STATE::Suspicious);
}

void AFPSPatrolGuard::ResetOrientation()
{
	SetActorRotation(OriginalRotation);

	SetGuardState(EGUARD_AI_STATE::Idle);
}

void AFPSPatrolGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSPatrolGuard::SetGuardState(const EGUARD_AI_STATE & NewGuardState)
{
	if (NewGuardState == GuardState)
		return;

	GuardState = NewGuardState;

	OnGuardStateChanged(NewGuardState);
}
