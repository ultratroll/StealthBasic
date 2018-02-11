// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Hole")
	UStaticMeshComponent*	HoleMesh;

	UPROPERTY(EditAnywhere, Category = "Hole")
	USphereComponent* AtractorSphere;

	UPROPERTY(EditAnywhere, Category = "Hole")
	USphereComponent* DestructorSphere;

	UPROPERTY(EditAnywhere, Category = "Hole")
	float HoleForce= -7000.0f;

	UFUNCTION()
	void OnDestructionOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
