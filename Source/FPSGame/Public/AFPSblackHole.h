// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "AFPSblackHole.generated.h"

UCLASS()
class FPSGAME_API AAFPSblackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAFPSblackHole();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnyWhere,Category="Components")
	UStaticMeshComponent* MeshComp; 

	UPROPERTY(VisibleAnyWhere, Category = "Components")
	class USphereComponent*	OuterBlack; 
	UPROPERTY(VisibleAnyWhere, Category = "Components")
		class USphereComponent* InnerBlack;
	//this fumction is delage to handle overlap between InnerBlack and actor. 
	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
