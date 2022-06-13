// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

#include "Components/BoxComponent.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	FCollisionResponseContainer Response;
	Response.Pawn = ECollisionResponse::ECR_Block;
	Response.WorldStatic = ECollisionResponse::ECR_Block;
	Response.WorldDynamic = ECollisionResponse::ECR_Block;

	BoxCollision->SetCollisionResponseToChannels(Response);


}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

