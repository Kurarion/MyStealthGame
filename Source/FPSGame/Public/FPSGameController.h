// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSGameController.generated.h"

/**
 *
 */
UCLASS()
class FPSGAME_API AFPSGameController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnMissionComplete(APawn* FPSCharacter, bool bMissionSuccess);



};
