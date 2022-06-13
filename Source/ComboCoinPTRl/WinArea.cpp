// Fill out your copyright notice in the Description page of Project Settings.


#include "WinArea.h"

#include "PawnPlane.h"
#include "CustomPlaneController.h"
#include "Components/SphereComponent.h"
#include "kismet/GameplayStatics.h"
#include "particles/ParticleSystemComponent.h"

// Sets default values
AWinArea::AWinArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	RootComponent = SphereCollision;

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AWinArea::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AWinArea::ComponentBeginOverlap);
	
}

// Called every frame
void AWinArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWinArea::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		APawnPlane* Char = Cast<APawnPlane>(OtherActor);
		if (Char)
		{
			// Player Reach the Location == win	
			Char->SetGameOver(true);
		}
	}
}

