// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnyWhere, Category = "Components")
		class UBoxComponent* OverlapComp;
	UPROPERTY(VisibleAnyWhere, Category = "Components")
		UStaticMeshComponent* MeshComp;
	UFUNCTION()
		void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditAnyWhere, Category = "LaunchPad")
		float LaunchStrengh;
	UPROPERTY(EditAnyWhere, Category = "LaunchPad")
		float LaunchAngle;

	UPROPERTY(EditDefaultsOnly, Category = "LaunchPad")
		UParticleSystem* LaunchPadeffect; 
public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
