// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "FPSGameMode.h"
#include "DrawDebugHelpers.h"
#include <NavigationSystem.h>
#include <Blueprint\AIBlueprintHelperLibrary.h>

// Sets default values
AAIGuard::AAIGuard()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyPawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	MyPawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGuard::OnPawnSeen);
	MyPawnSensingComp->OnHearNoise.AddDynamic(this, &AAIGuard::OnNoiseHeard);
	this->GuardState = EAIState::Idle;
}

// Called when the game starts or when spawned
void AAIGuard::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("COCOL BP"));	
	OriginalRotation = GetActorRotation();
	if (this->bPatrol)
	{
		this->NextPatrolPoint();
	}
					
}

void AAIGuard::NextPatrolPoint()
{
	//UE_LOG(LogTemp, Warning, TEXT("IM HERE2"))
	// first second 
	if (this->CurrentPatrolPoint == nullptr || this->CurrentPatrolPoint == this->FirestPatrolPoint)
	{
		this->CurrentPatrolPoint = this->SecondPatrolPoint;
	}
	else
	{
		this->CurrentPatrolPoint = this->FirestPatrolPoint;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), this->CurrentPatrolPoint);

}

void AAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn)
	{
		return;
	}
	else
	{
		DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 25, FColor::Blue, false, 10.f);
		AFPSGameMode* GM = Cast< AFPSGameMode>(GetWorld()->GetAuthGameMode());// WORK ONLY ON SERVER SIDE 
		if (!GM->MissionCompletedStaus())
		{
			/*	FString Debugmsg = FString::Printf(TEXT("IM HERE "));
				GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Blue, *Debugmsg);*/
			GM->CompleteMession(SeenPawn);
		}
		SetGuardState(EAIState::Alerted);
	}
}

void AAIGuard::OnNoiseHeard(APawn* NoiseInstagator, const FVector& Location, float Volume)
{
	if (this->GuardState == EAIState::Alerted)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), Location, 32.f, 25, FColor::Red, false, 10.f);
	FVector Direction = Location - GetActorLocation();// GetActorLocation is the location of the ai 
	Direction.Normalize();
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;
	SetActorRotation(NewLookAt);
	GetWorldTimerManager().ClearTimer(TimerResetOreination);
	GetWorldTimerManager().SetTimer(TimerResetOreination, this, &AAIGuard::ResetOrientation, 3.0f, false);
	SetGuardState(EAIState::Suspicious);
	AController* controller = GetController();
	if (controller)
	{
		controller->StopMovement();
	}
}

void AAIGuard::ResetOrientation()
{
	if (this->GuardState == EAIState::Alerted)
	{
		return;
	}
	SetActorRotation(OriginalRotation);
	SetGuardState(EAIState::Idle);
	if (bPatrol)
	{
		NextPatrolPoint();
	}
}

void AAIGuard::SetGuardState(EAIState NewState)
{
	if (this->GuardState == NewState)
		return;
	this->GuardState = NewState;
	OnStateChanged(GuardState);
}

// Called every frame
void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentPatrolPoint)
	{
		 FVector   Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
		 Delta.Z = 0;
		 UE_LOG(LogTemp, Warning, TEXT("im here vector %s"), *Delta.ToString());
		volatile float DistanceGoal = Delta.Size();
		UE_LOG(LogTemp, Warning, TEXT("im here dist %f"),DistanceGoal);
		if (DistanceGoal <50)
		{
			this->NextPatrolPoint();
		}
	}

}

//// Called to bind functionality to input
//void AAIGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

