// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowPoint.h"

#include "ComboCoinPTRlCharacter.h"
#include "CustomAIController.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFollowPoint::AFollowPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	
	OverlappingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Overlapping Sphere"));
	OverlappingSphere->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AFollowPoint::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);

	OverlappingSphere->OnComponentBeginOverlap.AddDynamic(this, &AFollowPoint::SphereBeginOverlap);
	OverlappingSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

}

// Called every frame
void AFollowPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AFollowPoint::SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		AComboCoinPTRlCharacter* Char = Cast<AComboCoinPTRlCharacter>(OtherActor);
		if(Char && Char != UGameplayStatics::GetPlayerCharacter(this, 0))
		{
			ACustomAIController* Cont = Char->GetAIController();
			if(Cont && Cont->GetNextPoint() == this)
			{
				Cont->GetNextFollowPoint();
				Cont->SetLastPoint(this);
			}
		}
	}
}

