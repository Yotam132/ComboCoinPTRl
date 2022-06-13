// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinArea.generated.h"

UCLASS()
class COMBOCOINPTRL_API AWinArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWinArea();

	/** SphereCollision */
	UFUNCTION()
	void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/** Win Area overlap Sphere */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USphereComponent* SphereCollision;

	/** Idle Particle */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UParticleSystemComponent* Particle;
};
