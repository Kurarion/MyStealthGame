// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "Engine/World.h"
#include "FPSGameController.h"


void AFPSGameState::OnMissionCompleted_Implementation(APawn* FPSCharacter, bool bMissionSuccess)
{
	//for (FConstPawnIterator PawnIt = GetWorld()->GetPawnIterator(); PawnIt;++PawnIt)
	//{
	//	APawn* pawn= PawnIt->Get();

	//	pawn->DisableInput(nullptr);
	//}

	for (FConstControllerIterator ControllerIt = GetWorld()->GetControllerIterator(); ControllerIt; ++ControllerIt)
	{
		AFPSGameController* FPSCon = Cast<AFPSGameController>(ControllerIt->Get());

		if (FPSCon&&FPSCon->IsLocalController())
		{
			FPSCon->OnMissionComplete(FPSCharacter, bMissionSuccess);

			APawn* FPSPawn = ControllerIt->Get()->GetPawn();
			if (FPSPawn)
			{
				FPSPawn->DisableInput(nullptr);
			}
		}


		
	}
}
