// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSGameMode.h"
#include "FPSCharacter.h"
#include "Engine/Engine.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	this->OverLapComp = CreateDefaultSubobject< UBoxComponent>(TEXT("OverLapComp"));
	this->OverLapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	this->OverLapComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	this->OverLapComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	this->OverLapComp->SetBoxExtent(FVector(200.f));
	RootComponent =  this->OverLapComp;
	OverLapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverLap);
	this->OverLapComp->SetHiddenInGame(false);
	DecalComponent= CreateDefaultSubobject< UDecalComponent>(TEXT("DecalComp"));
	DecalComponent->DecalSize = FVector(200.0f, 200.0f, 200.0f);
	this->DecalComponent->SetupAttachment(RootComponent);

}


void AFPSExtractionZone::HandleOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("IM HERE MANN!! "))
		AFPSCharacter* Mypawan = Cast< AFPSCharacter>(OtherActor);

		if (!Mypawan)
		{
			return; 
		}
	
		if ( Mypawan->bisCarryinObjective)
		{
			AFPSGameMode* GM = Cast< AFPSGameMode> (GetWorld()->GetAuthGameMode());// WORK ONLY ON SERVER SIDE 
			if (GM)
			{
			/*	FString Debugmsg = FString::Printf(TEXT("IM HERE "));
				GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Blue, *Debugmsg);*/
				
				GM->SetMissionComplete(true);
				GM->CompleteMession(Mypawan);

			}
		}
		else {
			//is tje soumd set in BP this->ObjectivwMissingSound
			UGameplayStatics::PlaySound2D(this, this->ObjectivwMissingSound);
		}
}

