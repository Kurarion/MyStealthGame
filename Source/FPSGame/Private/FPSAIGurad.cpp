// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGurad.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "AI/Navigation/NavigationSystem.h"
#include "GameFramework/Controller.h"
#include "Net/UnrealNetwork.h"
// Sets default values
AFPSAIGurad::AFPSAIGurad()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSence = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSence"));

	AIState = EAIState::Idle;
}

// Called when the game starts or when spawned
void AFPSAIGurad::BeginPlay()
{
	Super::BeginPlay();
	PawnSence->OnSeePawn.AddDynamic(this, &AFPSAIGurad::OnSeePawn);

	PawnSence->OnHearNoise.AddDynamic(this, &AFPSAIGurad::OnHearNoise);

	OriginRotation = GetActorRotation();

	NextPoint = FirstPoint;

	if (bStartWalk)
	{
		Walk();
	}
}

void AFPSAIGurad::OnSeePawn(APawn * Pawn)
{
	if (Pawn == nullptr)
	{
		return;
	}
	AFPSGameMode* myGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

	if (myGameMode)
	{
		myGameMode->MissionCompleted(Pawn, false);
	}

	DrawDebugSphere(GetWorld(), Pawn->GetActorLocation(), 20.0f, 12, FColor::Blue, true, 5.0f);

	SetAIState(EAIState::Found);


	AController* AIController = GetController();

	if (bStartWalk)
	{
		AIController->StopMovement();
	}
}

void AFPSAIGurad::OnHearNoise(APawn * NoiseInstigator, const FVector & Location, float Volume)
{
	if (AIState==EAIState::Found)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), Location, 20.0f, 12, FColor::Red, true, 5.0f);

	FVector Dir = Location - GetActorLocation();
	Dir.Normalize();
	FRotator NewLookDir = FRotationMatrix::MakeFromX(Dir).Rotator();
	NewLookDir.Pitch = 0;
	NewLookDir.Roll = 0;


	SetActorRotation(NewLookDir);

	GetWorldTimerManager().ClearTimer(TimeHandle_ResetRotation);
	GetWorldTimerManager().SetTimer(TimeHandle_ResetRotation, this, &AFPSAIGurad::OnResetRotation, 3.0f);


	SetAIState(EAIState::Suspicous);


	AController* AIController = GetController();

	if (bStartWalk)
	{
		AIController->StopMovement();
	}
}

void AFPSAIGurad::OnRep_AIStateChanged()
{
	OnBeenFound(AIState);
}

void AFPSAIGurad::SetAIState(EAIState newState)
{
	if(newState==AIState)
	{
		return;
	}
	AIState = newState;

	OnRep_AIStateChanged();
	
}

void AFPSAIGurad::OnResetRotation()
{
	if (AIState == EAIState::Found)
	{
		return;
	}

	SetActorRotation(OriginRotation);

	SetAIState(EAIState::Idle);

	UNavigationSystem::SimpleMoveToActor(GetController(), NextPoint);
}

void AFPSAIGurad::Walk()
{
	if (NextPoint == FirstPoint)
	{
		NextPoint = SecondPoint;
	}
	else
	{
		NextPoint = FirstPoint;
	}
	UNavigationSystem::SimpleMoveToActor(GetController(), NextPoint);
}

// Called every frame
void AFPSAIGurad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (NextPoint)
	{
		FVector Dis = GetActorLocation()- NextPoint->GetActorLocation();
		float Distance = Dis.Size();

		if (Distance < 200) 
		{
			//UE_LOG(LogTemp, Log, TEXT("xxxx"));
			Walk();
		}


	}
}

void AFPSAIGurad::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSAIGurad, AIState);
}



