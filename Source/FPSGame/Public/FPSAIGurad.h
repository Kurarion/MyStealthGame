// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGurad.generated.h"

class UPawnSensingComponent;

UCLASS()
class FPSGAME_API AFPSAIGurad : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGurad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "AI")
		UPawnSensingComponent* PawnSence;

	UFUNCTION()
		void OnSeePawn(APawn* Pawn);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
