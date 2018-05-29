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

	LaunchPadBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchPadTrigger"));
	LaunchPadBox->SetBoxExtent(FVector(85, 85, 40));
	RootComponent = LaunchPadBox;

	LaunchPadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchPad"));
	LaunchPadMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LaunchPadMesh->SetupAttachment(LaunchPadBox);

	bUsePushAngle = true;
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

	FRotator Rotation = this->GetActorRotation();
	Rotation.Pitch += LaunchPitchAngle;
	const FVector Push = Rotation.Vector() * PushForce;

	if (Character)
	{
		Character->LaunchCharacter(Push, true, true);
		//	Character->LaunchCharacter(PushDirection*PushForce, true, true);
	}
	else
	{
		if (OtherComponent && OtherComponent->IsSimulatingPhysics())
		{
			OtherComponent->AddImpulse(Push, NAME_None, true);
			UE_LOG(LogTemp, Log, TEXT("PUSH!"));
		}
	}
}

// Called every frame
void AFPSLaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

