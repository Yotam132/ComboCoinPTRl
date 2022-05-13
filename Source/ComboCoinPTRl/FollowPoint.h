// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FollowPoint.generated.h"

UCLASS()
class COMBOCOINPTRL_API AFollowPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFollowPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

private:
	/** Mesh */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMeshComponent* Mesh;

	/** Overlap Sphere */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USphereComponent* OverlappingSphere;

};

