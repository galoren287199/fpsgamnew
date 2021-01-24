// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
// Sets default values
ALaunchPad::ALaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;
	this->OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverLapComp"));
	this->OverlapComp->SetBoxExtent(FVector(75, 75, 50)); // need to check

	this->OverlapComp->SetupAttachment(MeshComp);
	this->OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::OverlapLaunchPad);

	this->LaunchStrengh = 1500;// defualt value.. 
	this->LaunchAngle = 35.0f;
	
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALaunchPad::OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch = LaunchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrengh;// this is how tranfrom to speed . 
	ACharacter* OtherCharachter = Cast< ACharacter>(OtherActor);
	FString Debugmsg = FString::Printf(TEXT("IM HERE "));
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Blue, *Debugmsg);

	if (OtherCharachter)
	{
		// launch playr both bolleans give consistent launch velocirt by ignoring the current player velocity. 
		OtherCharachter->LaunchCharacter(LaunchVelocity, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchPadeffect, GetActorLocation());
	}

}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

