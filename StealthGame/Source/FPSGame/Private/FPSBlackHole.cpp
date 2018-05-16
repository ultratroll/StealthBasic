// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//UStaticMeshComponent*	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));

	HoleMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hole"));
	HoleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = HoleMesh;

	AtractorSphere= CreateDefaultSubobject<USphereComponent>(TEXT("AtractionTrigger"));
	AtractorSphere->SetupAttachment(HoleMesh);

	DestructorSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DestructionTrigger"));
	DestructorSphere ->SetSphereRadius(100);
	DestructorSphere->SetupAttachment(HoleMesh);
}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();
	DestructorSphere->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::OnDestructionOverlap);
}

void AFPSBlackHole::OnDestructionOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor)
		OtherActor->Destroy();
}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingActors;
	AtractorSphere->GetOverlappingComponents(OverlappingActors);

	for (int32 i = 0; i < OverlappingActors.Num(); ++i)
	{
		UPrimitiveComponent* OverActor = OverlappingActors[i];
		if (OverActor && !OverActor->IsPendingKill() && OverActor->IsSimulatingPhysics())
		{
			const float Radius = AtractorSphere->GetScaledSphereRadius();
			const float Strenght = HoleForce;
			OverActor->AddRadialForce(GetActorLocation(), Radius, Strenght, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}

}

