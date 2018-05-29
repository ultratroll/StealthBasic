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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensingComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
