// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinSpawner.h"

#include "Coin.h"
#include "ComboCoinPTRlCharacter.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACoinSpawner::ACoinSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;

	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Instanced Static Mesh"));
	InstancedStaticMesh->SetupAttachment(GetRootComponent());

	StaticMesh = nullptr;
	ObjectToSpawn = nullptr;
	
	ObjectDistancing = 100.f;

	CoinAmount = 0;
	ComboCoinValue = 10;
}

void ACoinSpawner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(StaticMesh)
	{
		InstancedStaticMesh->SetStaticMesh(StaticMesh);
		InstancedStaticMesh->ClearInstances();
	}
	
	uint8 Index = static_cast<uint8>(Spline->GetSplineLength() / ObjectDistancing);
	float DistanceNow = 0.f;
	
	for(int i = 0; i < Index + 1; i++)
	{
		FVector Location = Spline->GetLocationAtDistanceAlongSpline(DistanceNow, ESplineCoordinateSpace::Local);
		float ZRot = FMath::FRandRange(-180.f, 180.f);
		FRotator Rotation = FRotator(0.f, ZRot, 0.f);
		FQuat Quat = FQuat(Rotation);

		FTransform CoinTransform;
		CoinTransform.SetLocation(Location);
		CoinTransform.SetRotation(Quat);
		
		InstancedStaticMesh->AddInstance(CoinTransform);
		
		DistanceNow += ObjectDistancing;
	}
}

// Called when the game starts or when spawned
void ACoinSpawner::BeginPlay()
{
	Super::BeginPlay();

	uint8 Index = static_cast<uint8>(Spline->GetSplineLength() / ObjectDistancing);
	float DistanceNow = 0.f;

	InstancedStaticMesh->ClearInstances();
	
	if(!ObjectToSpawn)
	{
		return;
	}
	
	for(int i = 0; i < Index + 1; i++)
	{
		FVector Location = Spline->GetLocationAtDistanceAlongSpline(DistanceNow, ESplineCoordinateSpace::World);
		float ZRot = FMath::FRandRange(-180.f, 180.f);
		FRotator Rotation = FRotator(0.f, ZRot, 0.f);
		FQuat Quat = FQuat(Rotation);
	
		FTransform CoinTransform;
		CoinTransform.SetLocation(Location);
		CoinTransform.SetRotation(Quat);

		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		CoinAmount += 1;
		ACoin* Coin = Cast<ACoin>(GetWorld()->SpawnActor<AActor>(ObjectToSpawn, CoinTransform, Param));
		if(Coin)
		{
			Coin->SetCoinSpawner(this);
		}
		
		if (i == Index && WinAreaToSpawn)
		{
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			GetWorld()->SpawnActor<AActor>(WinAreaToSpawn, CoinTransform, Param);
		}
		
		DistanceNow += ObjectDistancing;
	}

}

void ACoinSpawner::MinusCoinAmountByOne()
{
	CoinAmount -= 1;
	UE_LOG(LogTemp, Warning, TEXT("%d"), CoinAmount);
	if(CoinAmount <= 0)
	{
		AComboCoinPTRlCharacter* Char = Cast<AComboCoinPTRlCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if(Char)
		{
			Char->AddCoinByValue(ComboCoinValue);
		}
	}
}

