// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Pad")
	UStaticMeshComponent*	LaunchPadMesh;

	UPROPERTY(EditAnywhere, Category = "Pad")
	UBoxComponent* LaunchPadBox;

	UPROPERTY(EditAnywhere, Category = "Pad")
	float PushForce= 7000.0f;

	UPROPERTY(EditAnywhere, Category = "Pad")
	FVector PushDirection;

	UFUNCTION()
	void OnLaunchPadOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
