// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMeshComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::JumpFunc);

	LaunchSpeed = 1500.0f;
	LaunchAngle = 45.0f;
}


void AFPSLaunchPad::JumpFunc(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	FRotator LaunchArrow=GetActorRotation();
	LaunchArrow.Pitch += LaunchAngle;
	FVector LaunchVelocity = LaunchArrow.Vector()*LaunchSpeed;

	ACharacter* myCharacter = Cast<ACharacter>(OtherActor);
	if (myCharacter)
	{
		myCharacter->LaunchCharacter(LaunchVelocity, true, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), JumpFX, GetActorLocation());
	}
	if (OtherComp&&OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), JumpFX, GetActorLocation());
	}
}


