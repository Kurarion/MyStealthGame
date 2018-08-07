// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "Engine/World.h"



void AFPSGameState::OnMissionCompleted_Implementation(APawn* FPSCharacter, bool bMissionSuccess)
{
	

	for (FConstPawnIterator PawnIt = GetWorld()->GetPawnIterator(); PawnIt;++PawnIt)
	{
		APawn* pawn= PawnIt->Get();

		pawn->DisableInput(nullptr);
	}
}
