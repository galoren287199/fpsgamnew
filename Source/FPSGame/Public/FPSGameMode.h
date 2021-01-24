// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"


UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly ,Category = "ViewPort" )
	TSubclassOf<AActor> ViewPort;
	bool MissionCompleted; 
public:

	AFPSGameMode();
	void CompleteMession(APawn* MY_pwan);// add oprion to failure by bMissionSuccess
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnMessionCompleted(APawn* MY_pwan, bool bMissionSuccess);// add oprion to failure by bMissionSuccess
	bool MissionCompletedStaus();
	void SetMissionComplete(bool status );

};



