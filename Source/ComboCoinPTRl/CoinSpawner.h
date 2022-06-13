// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinSpawner.generated.h"

UCLASS()
class COMBOCOINPTRL_API ACoinSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinSpawner();

	virtual void OnConstruction(const FTransform& Transform) override;

	/** Minus Coin Amount By One */
	void MinusCoinAmountByOne();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Spline Component */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USplineComponent* Spline;

	/** Instanced Static Mesh */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UInstancedStaticMeshComponent* InstancedStaticMesh;
	
	/** Static Mesh Object */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMesh* StaticMesh;

	/** Object To Spawn */
	UPROPERTY(EditAnywhere, Category = "Spawns")
	TSubclassOf<AActor> ObjectToSpawn;

	/** Win Area To Spawn */
	UPROPERTY(EditAnywhere, Category = "Spawns")
	TSubclassOf<AActor> WinAreaToSpawn;

	/** Distance between Object */
	UPROPERTY(EditAnywhere, Category = "Spawns")
	float ObjectDistancing;

	/** Coin Amount In Spline */
	UPROPERTY(VisibleAnywhere, Category = "Coin")
	uint8 CoinAmount;
	
	/** Combo Coin Value */
	UPROPERTY(EditAnywhere, Category = "Coin")
	uint8 ComboCoinValue;
};
