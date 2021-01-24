// Fill out your copyright notice in the Description page of Project Settings.


#include "FpsObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AFpsObjectiveActor::AFpsObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;
	SphereComp=CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));  
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//ignore all
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//enable for player
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	// in the tree airerchy 
	SphereComp->SetupAttachment(MeshComp);
	//	SphereComp->OnComponentBeginOverlap(fiil actor here  );
	
}

// Called when the game starts or when spawned
void AFpsObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	PlayEffects();
}

void AFpsObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, particle, GetActorLocation());
}

//// Called every frame
//void AFpsObjectiveActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}


//notify when actor overlap 
//---could be done also
void AFpsObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayEffects();
	AFPSCharacter* Mycharchter = Cast< AFPSCharacter>(OtherActor); 
	if (Mycharchter)
	{
		Mycharchter->bisCarryinObjective = true;
		Destroy();
	}
	
}

