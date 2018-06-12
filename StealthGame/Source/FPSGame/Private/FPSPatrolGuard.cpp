// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPatrolGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFPSPatrolGuard::AFPSPatrolGuard()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AFPSPatrolGuard::OnSeenPawn);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AFPSPatrolGuard::OnNoiseHeard);

	GuardState = EGUARD_AI_STATE::Idle;
}

void AFPSPatrolGuard::OnRep_GuardState()
{
	OnGuardStateChanged(GuardState); // LEts change the UI reaction in blueprint
}

void AFPSPatrolGuard::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalRotation = GetActorRotation();

	if (bPatrol)
		MoveNextPatrolPoint();
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
		
		if (AController* Controller = GetController())
		{
			Controller->StopMovement();
		}

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

	if (AController* Controller = GetController())
	{
		Controller->StopMovement();
	}
}

void AFPSPatrolGuard::ResetOrientation()
{
	SetActorRotation(OriginalRotation);

	SetGuardState(EGUARD_AI_STATE::Idle);

	MoveNextPatrolPoint();
}

void AFPSPatrolGuard::MoveNextPatrolPoint()
{
	if (bPatrol)
	{
		if (!IsValid(CurrentPatrolPoint))
		{
			if (PatrolPoints.Num() > 0)
			{
				CurrentPatrolPoint = PatrolPoints[0];
			}
			else
			{
				bPatrol= false;
			}
		}
		else
		{
			CurrentPatrolPointIdx++;
			if (PatrolPoints.Num() < CurrentPatrolPointIdx)
				CurrentPatrolPointIdx = 0;

			CurrentPatrolPoint = PatrolPoints[CurrentPatrolPointIdx];
		}
		
		UNavigationSystem::SimpleMoveToActor(GetController(), CurrentPatrolPoint);
	}
}

void AFPSPatrolGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(CurrentPatrolPoint) && bPatrol)
	{
		const float Distance = (CurrentPatrolPoint->GetActorLocation() - this->GetActorLocation()).Size();

		if (Distance < MinimalDistance)
		{
			MoveNextPatrolPoint();
		}
	}
}

void AFPSPatrolGuard::SetGuardState(const EGUARD_AI_STATE & NewGuardState)
{
	if (NewGuardState == GuardState)
		return;

	GuardState = NewGuardState; // This is done in server only (called from AI methods) and will trigger OnRep_GuardState calls on all clients (not server).

	OnRep_GuardState(); // Since OnRep_GuardState is only called in clients, and SetGuardState only called from AI methods (that only work in server), we call this here
	// so that reactions UI on dwarf guards also happen in server
}

/** Setting the rules of how variables are going to be replicated (one client?, multiple clients?, ect). */
void AFPSPatrolGuard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSPatrolGuard, GuardState);
}
