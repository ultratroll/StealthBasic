// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	OverlapArea = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapArea"));
	OverlapArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapArea->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapArea->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapArea->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapArea;

	OverlapArea->SetHiddenInGame(false);
	OverlapArea->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::OnAreaOverlap);
}

// Called when the game starts or when spawned
void AFPSExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSExtractionZone::OnAreaOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("Entering extraction zone"));
}

