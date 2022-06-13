// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

#include "CoinSpawner.h"
#include "PawnPlane.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereCollision->SetupAttachment(GetRootComponent());

	RotationSpeed = 1.f;
	
	Value = 1;

	PickupSoundCue = nullptr;
	CoinSpawner = nullptr;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoin::ComponentBeginOverlap);

	GetWorld()->GetTimerManager().SetTimer(RotationTimerHandle, this, &ACoin::Rotate, 0.05f, true);
}


// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoin::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		APawnPlane* Char = Cast<APawnPlane>(OtherActor);
		if(Char)
		{
			Char->AddPlanePointByValue(Value);
			if(CoinSpawner)
			{
				CoinSpawner->MinusCoinAmountByOne();
			}
			
			UGameplayStatics::PlaySound2D(this, PickupSoundCue);
			Destroy();
		}
	}
}

void ACoin::SetCoinSpawner(ACoinSpawner* Spawner)
{
	if(Spawner)
	{
		CoinSpawner = Spawner;
	}
}

void ACoin::Rotate()
{
	FRotator Rot = FRotator(0.f, RotationSpeed, 0.f);
	AddActorLocalRotation(Rot);
}

void ACoin::PlaySoundCoin()
{
	if(PickupSoundCue)
	{
		UGameplayStatics::PlaySound2D(this, PickupSoundCue);
	}
}


