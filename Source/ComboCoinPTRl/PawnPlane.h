// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnPlane.generated.h"


UENUM(BlueprintType)
enum class EPlaneState : uint8
{
	EPS_OnLand	 	UMETA(DisplayName = "OnLand"),
	EPS_Fly		 	UMETA(DisplayName = "Fly"),
	EPS_Falling		UMETA(DisplayName = "Falling"),

	EPS_DefaultMax	UMETA(DisplayName = "DefaultMAX")
};


UCLASS()
class COMBOCOINPTRL_API APawnPlane : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnPlane();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Getter n Setter for Plane Point */
	void SetPlanePoint(int32 Point);

	UFUNCTION(BlueprintPure)
	int32 GetPlanePoint();

	/** Getter n Setter for Plane Movement Speed */
	void SetPlaneMovementSpeed(float Speed);

	UFUNCTION(BlueprintPure)
	float GetPlaneMovementSpeed();

	/** Get the plane max speed */
	UFUNCTION(BlueprintPure)
	float GetPlaneMaximumMovementSpeed();

	/** Get the plane minimum speed to fly */
	UFUNCTION(BlueprintPure)
	float GetPlaneMinimumSpeedToFly();

	/** Get Plane Highness now */
	UFUNCTION(BlueprintPure)
	float GetPlaneHighness();

	/** Get Plane Maximum Highness now */
	UFUNCTION(BlueprintPure)
	float GetPlaneMaximumHighness();

	/** Calculate plane position in air */
	UFUNCTION(BlueprintPure)
	float GetPlaneLocationZ();

	/**
	* Add Plane Point By Value 
	* 
	* @param Value - The value that gonna added to PlanePoint 
	*/
	void AddPlanePointByValue(int32 Value);

	/*
	* Set Game Over
	* 
	* @param bValue - if True then win, else lose
	*/
	void SetGameOver(bool bValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Plane State */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Planes", meta = (allowPrivateAccess = "true"))
	EPlaneState PlaneState;

	/** Mesh */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMeshComponent* Mesh;

	/** Plane Collision */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UCapsuleComponent* CapsuleCollision;

	/** Arrow Component */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UArrowComponent* ArrowPoint;

	/** SpringArmComponent */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USpringArmComponent* SpringArm;

	/** The Camera */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UCameraComponent* Camera;

	/** Plane Movement Speed */
	UPROPERTY(EditAnywhere, Category = "Controls | Movement")
	float MovementSpeed;
	
	/** Plane Maximum Movement Speed */
	UPROPERTY(EditAnywhere, Category = "Controls | Movement")
	float MaximumMovementSpeed;
	
	/** Plane Acceleration */
	UPROPERTY(EditAnywhere, Category = "Controls | Movement")
	float PlaneAcceleration;

	/** Plane Direction */
	UPROPERTY(VisibleAnywhere, Category = "Controls")
	FVector PlaneDirection;

	/** Rotation Rate */
	UPROPERTY(EditAnywhere, Category = "Controls | Rotation")
	float RotationRate;

	/** New Rotation Yaw */
	UPROPERTY(EditAnywhere, Category = "Controls | Rotation")
	float TargetYawRotation;

	/** boolean for handling is rotating or not */
	UPROPERTY(EditAnywhere, Category = "Controls | Rotation")
	bool bRotatingPlane;

	/** Fly Rate */
	UPROPERTY(EditAnywhere, Category = "Controls | Fly")
	float FlyRate;

	/** Default Z Location */
	UPROPERTY(VisibleAnywhere, Category = "Controls | Fly")
	float DefaultZLocation;
	
	/** Max Z Location */
	UPROPERTY(VisibleAnywhere, Category = "Controls | Fly")
	float MaximumHighness;
	
	/** is Plane Flying */
	UPROPERTY(VisibleAnywhere, Category = "Controls | Fly")
	bool bFlying;

	/** The minimum speed to make the plane able to fly. Below it will be fall */
	UPROPERTY(VisibleAnywhere, Category = "Controls | Fly")
	float MinimumSpeedToFly;
	
	/** Gravity (Falling Speed / s) */
	UPROPERTY(EditAnywhere, Category = "Controls | Fly")
	float Gravity;

	/** Is it time to call timer yet or not */
	UPROPERTY(EditAnywhere, Category = "Controls | Fly")
	bool bCallFlyTimer;

	/** Target Pitch Rotation */
	UPROPERTY(EditAnywhere, Category = "Controls | Fly")
	float TargetPitchRotation;

	FTimerHandle FlyTimerHandle;
	
	/** Plane Point */
	UPROPERTY(VisibleAnywhere, Category = "Gameplays | Point")
	int32 PlanePoint;

	/** is Game ended or not */
	UPROPERTY(VisibleAnywhere, Category = "Gameplays | Debug")
	bool bGameEnd;

	/** Plane Controller */
	UPROPERTY(VisibleAnywhere, Category = "Gameplays | Controllers")
	class ACustomPlaneController* PlaneController;
	
	/**
	*	FUNCTION PLACE
	*/

	/** Speed Up / Slow Down */
	void SpeedUp(float Value);

	/** Rotate Right / Left */
	void RotateRight(float Value);

	/** Fly Up / Down */
	void FlyUp(float Value);

	/** Plane Accelerate */
	void PlaneAccelerate(float Delta);

	/** Plane Release Rotating */
	void ReleaseRotation();

	/** Plane Release Fly */
	void ReleaseFly();

	/** Adding Plane local offset, and checking for Hitted Object */
	void AddPlaneLocalOffset(FVector Location, FHitResult* HitResult);

	/** Set Fly To False */
	void SetFlyToFalse();
};
