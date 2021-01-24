// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "AIGuard.generated.h"
class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState:uint8 
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AAIGuard : public ACharacter
{
	GENERATED_BODY()
		
public:
	// Sets default values for this character's properties
	AAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnyWhere,Category="Components")
	UPawnSensingComponent* MyPawnSensingComp;

	UPROPERTY(EditInstanceOnly, Category = "AI")
		bool bPatrol;
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
		AActor* FirestPatrolPoint;
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
		AActor* SecondPatrolPoint;

	AActor* CurrentPatrolPoint;
	void NextPatrolPoint();

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstagator, const FVector& Location, float Volume);
	UFUNCTION()
		void ResetOrientation();
	FRotator OriginalRotation; 
	FTimerHandle  TimerResetOreination;
	EAIState GuardState;
	UFUNCTION()
	void SetGuardState(EAIState NewState);
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void OnStateChanged(EAIState GuardState);

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
