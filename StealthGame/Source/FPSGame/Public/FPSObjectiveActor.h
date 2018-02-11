// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	
	UPROPERTY(EditAnywhere, Category= "Base")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere, Category= "Base")
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* PickupFX;

	virtual void BeginPlay() override;

	void PlayEffects();

public:	

	/* Lets override this method. */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
