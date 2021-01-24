// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
	this->MissionCompleted = false;

}

//change complet mession to option of to failure if seen 
void AFPSGameMode::CompleteMession(APawn* MY_pwan)
{
	if (MY_pwan)
	{
		MY_pwan->DisableInput(nullptr);// diable input from the [pawn sont care if we send player controller or not . 
		// if did asssignment to tsubclassobject
		if (this->ViewPort)
		{

			//create actor 
			AActor* NewViewTarget=nullptr; 
			TArray <AActor*> ReturnedActors;
			//get all actor in type of this->ViewPort 
			UGameplayStatics::GetAllActorsOfClass(this, this->ViewPort, ReturnedActors);
			if (ReturnedActors.Num() > 0)
			{
				//get the first result
				NewViewTarget = ReturnedActors[0];
				APlayerController* PlayerContrller = Cast< APlayerController>(MY_pwan->GetController());
				if (PlayerContrller)
				{
					PlayerContrller->SetViewTargetWithBlend(NewViewTarget, 3.0f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else {
		UE_LOG(LogTemp,Warning,TEXT("ViewPort is nullptr, please update GameMode class with valid sublass. cannot spectating view target. "))
		}
	}
	OnMessionCompleted(MY_pwan,this->MissionCompletedStaus());
}

bool AFPSGameMode::MissionCompletedStaus()
{
	return this->MissionCompleted;
}

void AFPSGameMode::SetMissionComplete(bool status)
{
	this->MissionCompleted = status;
}

