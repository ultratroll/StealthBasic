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

	/** Force of push. */
	UPROPERTY(EditAnywhere, Category = "Pad")
	float PushForce= 7000.0f;

	/** Angle to push if bUsePushAngle is set to true. */
	UPROPERTY(EditAnywhere, Category = "Pad")
	float LaunchPitchAngle= 35.0f;

	/** Used to define direction instead of angle when the bUsePushAngle flag is off. */
	UPROPERTY(EditAnywhere, Category = "Pad")
	FVector PushDirection;

	/** If true, push using the angle instead of the direction. */
	UPROPERTY(EditAnywhere, Category = "Pad")
	uint8 bUsePushAngle : 1;

	UFUNCTION()
	void OnLaunchPadOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
