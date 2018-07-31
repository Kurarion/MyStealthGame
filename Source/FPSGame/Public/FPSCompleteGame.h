// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSCompleteGame.generated.h"

class UBoxComponent;
class UDecalComponent;
class USoundBase;

UCLASS()
class FPSGAME_API AFPSCompleteGame : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSCompleteGame();

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
		USoundBase* FailedMission;
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UDecalComponent* DecalComp;
	UFUNCTION()
		void HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	
};
