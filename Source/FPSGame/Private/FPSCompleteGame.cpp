// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCompleteGame.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "kismet/GameplayStatics.h"

// Sets default values
AFPSCompleteGame::AFPSCompleteGame()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComp->SetBoxExtent(FVector(200.0f));
	BoxComp->SetHiddenInGame(false);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSCompleteGame::HandleCollision);
	RootComponent = BoxComp;

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f, 200.0f, 200.0f);
	DecalComp->SetupAttachment(BoxComp);

}

void AFPSCompleteGame::HandleCollision(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	

	AFPSCharacter* myCharacter = Cast<AFPSCharacter>(OtherActor);
	if (myCharacter==nullptr)
	{
		return;
	}

	


	if (myCharacter->bIsCarryingObjective == true)
	{
		UE_LOG(LogTemp, Log, TEXT("OK!!!"));

		AFPSGameMode* myGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

		if (myGameMode)
		{
			myGameMode->MissionCompleted(myCharacter, true);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, FailedMission);
	}
}
