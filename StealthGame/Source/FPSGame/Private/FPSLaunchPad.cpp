// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FPSCharacter.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//UStaticMeshComponent*	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));

	LaunchPadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchPad"));
	LaunchPadMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = LaunchPadMesh;


	LaunchPadBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchPadTrigger"));
	LaunchPadBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LaunchPadBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	LaunchPadBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	LaunchPadBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	LaunchPadBox->SetBoxExtent(FVector(200.0f));
	LaunchPadBox->SetupAttachment(LaunchPadMesh);
}

// Called when the game starts or when spawned
void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();
	LaunchPadBox->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::OnLaunchPadOverlap);

	PushDirection = this->GetActorForwardVector() + this->GetActorUpVector();
}

void AFPSLaunchPad::OnLaunchPadOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);

	if (Character)
	{
		Character->LaunchCharacter(PushDirection*PushForce, true, true);
	}
	else
	{
		if (OtherComponent)
		{
			OtherComponent->AddForce(PushDirection*PushForce);
		}
	}
}

// Called every frame
void AFPSLaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

