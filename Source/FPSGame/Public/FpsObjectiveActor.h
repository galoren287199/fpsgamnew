// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSCharacter.h"
#include "FpsObjectiveActor.generated.h"

UCLASS()
class FPSGAME_API AFpsObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFpsObjectiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnyWhere,Category="Components")
	UStaticMeshComponent* MeshComp; 
	UPROPERTY(VisibleAnyWhere, Category = "Components")
	class USphereComponent* SphereComp; 
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* particle; 

	void PlayEffects(); 
public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
