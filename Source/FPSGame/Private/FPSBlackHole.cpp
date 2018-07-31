// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = meshComp;

	innerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphere"));
	innerSphereComp->SetSphereRadius(300);
	innerSphereComp->SetupAttachment(meshComp);

	

	outerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphere"));
	outerSphereComp->SetSphereRadius(3000);
	outerSphereComp->SetupAttachment(meshComp);



}

// Called when the game starts or when spawnead
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();

	innerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::OverlapInnerSphereComp);
}

void AFPSBlackHole::OverlapInnerSphereComp(UPrimitiveComponent* overlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComps;

	outerSphereComp->GetOverlappingComponents(OverlappingComps);

	for(int32 i = 0; i<OverlappingComps.Num(); ++i)
	{
		UE_LOG(LogTemp, Log, TEXT("Tick"));
		UPrimitiveComponent* PrimComp = OverlappingComps[i];
		if (PrimComp&&PrimComp->IsSimulatingPhysics()) 
		{
			const float SphereRadius = outerSphereComp->GetScaledSphereRadius();
			const float ForeStrength = -2000;
			UE_LOG(LogTemp, Log, TEXT("Force Tick"));
			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForeStrength,ERadialImpulseFalloff::RIF_Constant,true);
		}
	}
}

