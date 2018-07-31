// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UStaticMeshComponent* meshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		USphereComponent* outerSphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		USphereComponent* innerSphereComp;

	UFUNCTION()
		void OverlapInnerSphereComp(UPrimitiveComponent* overlapComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,bool FromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
