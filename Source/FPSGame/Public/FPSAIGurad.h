// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGurad.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,

	Suspicous,

	Found
};

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

	UFUNCTION()
		void OnHearNoise(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FRotator OriginRotation;

	FTimerHandle TimeHandle_ResetRotation;

	EAIState AIState;

	void SetAIState(EAIState newState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void OnBeenFound(EAIState GuradState);

	UFUNCTION()
		void OnResetRotation();

	UPROPERTY(EditInstanceOnly, Category = "AISettings")
		bool bStartWalk;

	UPROPERTY(EditInstanceOnly, Category = "AISettings", meta = (EditCondition = "bStartWalk"))
		AActor *FirstPoint;

	UPROPERTY(EditInstanceOnly, Category = "AISettings", meta = (EditCondition = "bStartWalk"))
		AActor *SecondPoint;

	UPROPERTY(VisibleInstanceOnly, Category = "AISettings", meta = (EditCondition = "bStartWalk"))
		AActor* NextPoint;

	void Walk();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
