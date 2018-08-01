// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGurad.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AFPSAIGurad::AFPSAIGurad()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSence = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSence"));

}

// Called when the game starts or when spawned
void AFPSAIGurad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSAIGurad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



