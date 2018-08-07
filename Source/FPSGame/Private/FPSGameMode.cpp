// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"
#include "Engine/World.h"
AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();


}

void AFPSGameMode::MissionCompleted(APawn* FPSCharacter, bool status)
{
	if (FPSCharacter)
	{
		if (SpectatingViewpointClass) {
			//FPSCharacter->DisableInput(nullptr);
			AFPSGameState* GS = GetGameState<AFPSGameState>();
			GS->OnMissionCompleted(FPSCharacter, status);

			TArray<AActor*> ReturnedActor;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActor);

			if (ReturnedActor.Num() > 0) {
				AActor* NewViewTarget = ReturnedActor[0];

				//APlayerController* PC = Cast<APlayerController>(FPSCharacter->GetController());

				//if (PC)
				//{
				//	PC->SetViewTargetWithBlend(NewViewTarget, 2.0f, EViewTargetBlendFunction::VTBlend_Cubic);
				//}
				for (FConstControllerIterator ConIt = GetWorld()->GetControllerIterator(); ConIt; ++ConIt)
				{
					APlayerController* PC = Cast<APlayerController>(ConIt->Get());
					if (PC)
					{
						PC->SetViewTargetWithBlend(NewViewTarget, 2.0f, EViewTargetBlendFunction::VTBlend_Cubic);

					}

				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Set the SpectatingViewpointClass!"));
		}

	}

	OnMissionComplete(FPSCharacter, status);
}

