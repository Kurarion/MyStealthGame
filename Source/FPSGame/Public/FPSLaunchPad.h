// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"


class UParticleSystem;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "FX")
		UParticleSystem* JumpFX;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UBoxComponent* BoxComp;

	UFUNCTION()
		void JumpFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditInstanceOnly, Category = "JumpSettings")
		float LaunchSpeed;

	UPROPERTY(EditInstanceOnly, Category = "JumpSettings")
		float LaunchAngle;

	
	
};
