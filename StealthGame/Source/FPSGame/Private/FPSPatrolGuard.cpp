// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPatrolGuard.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AFPSPatrolGuard::AFPSPatrolGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
}

// Called when the game starts or when spawned
void AFPSPatrolGuard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSPatrolGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

