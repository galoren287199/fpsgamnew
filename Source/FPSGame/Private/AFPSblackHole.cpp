// Fill out your copyright notice in the Description page of Project Settings.


#include "AFPSblackHole.h"

// Sets default values
AAFPSblackHole::AAFPSblackHole()
{
	PrimaryActorTick.bCanEverTick = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	RootComponent = MeshComp;

	this->InnerBlack = CreateDefaultSubobject < USphereComponent>(TEXT("InnnerSphereComp"));
	this->InnerBlack->SetSphereRadius(100);
	this->InnerBlack->SetupAttachment(MeshComp);
	this->InnerBlack->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	this->OuterBlack= CreateDefaultSubobject < USphereComponent>(TEXT("OuterSphereComp"));
	this->OuterBlack->SetSphereRadius(3000);
	this->OuterBlack->SetupAttachment(MeshComp);
	this->OuterBlack->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	// bind delage to function that destroy the object 
	this->InnerBlack->OnComponentBeginOverlap.AddDynamic(this, &AAFPSblackHole::OverlapInnerSphere);
}

// Called when the game starts or when spawned
void AAFPSblackHole::BeginPlay()
{
	Super::BeginPlay();
	InnerBlack->OnComponentBeginOverlap.AddDynamic(this, &AAFPSblackHole::OverlapInnerSphere);
}




void AAFPSblackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
		OtherActor->Destroy();
}

// Called every frame
void AAFPSblackHole::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	TArray<UPrimitiveComponent*> OverlappingComps;
	OuterBlack->GetOverlappingComponents(OverlappingComps);
	//UE_LOG(LogTemp,Warning,TEXT("IM here"))
	const float SphereRadious = OuterBlack->GetScaledSphereRadius();
	const float Force = -10000;
	for (int i = 0; i < OverlappingComps.Num(); i++)
	{
		if (OverlappingComps[i] && OverlappingComps[i]->IsSimulatingPhysics())
		{
			OverlappingComps[i]->AddRadialForce(GetActorLocation(), SphereRadious, Force, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
	//DrawDebugString(GetWorld(),Hit.ImpactPoint,"Impact",nullptr,FColor::White,2.0,true)//nulptr at plave atcach to specipic actor ,Hit.ImpactPoint-whertr to print,2.0 IS duration,true-> draw a shadow
}


//cheak add impulse for player 
//check diffrecne add impulse and addradialforce 
//   