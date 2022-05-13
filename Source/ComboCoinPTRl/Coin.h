// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class COMBOCOINPTRL_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** SphereCollision */
	UFUNCTION()
	void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	/** Set Coin Spawner */
	void SetCoinSpawner(class ACoinSpawner* Spawner);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:
	/** Actor Mesh */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	/** Collision Component */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USphereComponent* SphereCollision;

	/** Value */
	UPROPERTY(EditAnywhere, Category = "Coin")
	int32 Value;
	
	/** Rotation Speed */
	UPROPERTY(EditAnywhere, Category = "Coin")
	float RotationSpeed;
	
	/** Pickup Sound Cue */
	UPROPERTY(EditAnywhere, Category = "Coin")
	class USoundCue* PickupSoundCue;

	/** Rotation Handle */
	FTimerHandle RotationTimerHandle;

	/** This Coin Spawner */
	UPROPERTY(VisibleAnywhere, Category = "Spawn")
	class ACoinSpawner* CoinSpawner;

	/** Rotating Object */
	void Rotate();

	/** Play Sound */
	void PlaySoundCoin();

};
