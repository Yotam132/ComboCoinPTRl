// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnPlane.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CustomPlaneController.h"
#include "Engine/StaticMesh.h"
#include "kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Wall.h"

// Sets default values
APawnPlane::APawnPlane()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	RootComponent = CapsuleCollision;

	ArrowPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Point"));
	ArrowPoint->SetupAttachment(GetRootComponent());

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(Mesh);
	SpringArm->TargetArmLength = 400.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	MovementSpeed = 0.f;
	MaximumMovementSpeed = 700.f;
	MaximumHighness = 150.f;
	PlaneAcceleration = 2.f;
	RotationRate = 2.f;
	FlyRate = 2.f;
	MinimumSpeedToFly = 250.f;
	Gravity = 200.f;

	PlanePoint = 0;

	PlaneDirection = FVector(0.f);
	PlaneState = EPlaneState::EPS_OnLand;

	bRotatingPlane = false;
	bFlying = false;
	bCallFlyTimer = true;
	bGameEnd = false;

}

// Called when the game starts or when spawned
void APawnPlane::BeginPlay()
{
	Super::BeginPlay();

	DefaultZLocation = GetActorLocation().Z;
	TargetYawRotation = GetActorRotation().Yaw;
	TargetPitchRotation = 0.f;

	PlaneController = Cast<ACustomPlaneController>(GetController());

	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	FCollisionResponseContainer Response;
	Response.Pawn = ECollisionResponse::ECR_Block;
	Response.WorldStatic = ECollisionResponse::ECR_Block;
	Response.WorldDynamic = ECollisionResponse::ECR_Block;

	CapsuleCollision->SetCollisionResponseToChannels(Response);
	
	SpringArm->bUsePawnControlRotation = true;

}

// Called every frame
void APawnPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGameEnd)
	{
		return;
	}

	PlaneAccelerate(DeltaTime);

	if (bRotatingPlane)
	{
		FRotator PlaneRotationNow = GetActorRotation();
		PlaneRotationNow.Roll = 0.f;

		PlaneRotationNow.Yaw = FMath::FInterpTo(PlaneRotationNow.Yaw, TargetYawRotation, DeltaTime, RotationRate);

		TargetYawRotation = PlaneRotationNow.Yaw;
		SetActorRotation(FQuat(FRotator(PlaneRotationNow)));
	}

	if (bFlying || PlaneState == EPlaneState::EPS_Falling)
	{
		FRotator PlaneRotationNow = GetActorRotation();
		if (PlaneState == EPlaneState::EPS_OnLand)
		{
			PlaneRotationNow.Pitch = FMath::FInterpTo(PlaneRotationNow.Pitch, TargetPitchRotation, DeltaTime, FlyRate + 3.f);
		}
		else
		{
			PlaneRotationNow.Pitch = FMath::FInterpTo(PlaneRotationNow.Pitch, TargetPitchRotation, DeltaTime, FlyRate);
		}

		SetActorRotation(FQuat(FRotator(PlaneRotationNow)));
	}
	else
	{
		TargetPitchRotation = 0.f;
		FRotator PlaneRotationNow = GetActorRotation();

		if (PlaneState == EPlaneState::EPS_OnLand)
		{
			PlaneRotationNow.Pitch = FMath::FInterpTo(PlaneRotationNow.Pitch, -.02f, DeltaTime, FlyRate * 1.4f);
		}
		else
		{
			PlaneRotationNow.Pitch = FMath::FInterpTo(PlaneRotationNow.Pitch, 0.f, DeltaTime, FlyRate / 5.5f);
		}

		SetActorRotation(FQuat(FRotator(PlaneRotationNow)));
	}
}

// Called to bind functionality to input
void APawnPlane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnPlane::SpeedUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &APawnPlane::RotateRight);
	PlayerInputComponent->BindAction("PlaneTurn", EInputEvent::IE_Released, this, &APawnPlane::ReleaseRotation);

	PlayerInputComponent->BindAxis("Fly", this, &APawnPlane::FlyUp);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void APawnPlane::SpeedUp(float Value)
{
	MovementSpeed += PlaneAcceleration * Value;
	MovementSpeed = FMath::Clamp<float>(MovementSpeed, 0.f, MaximumMovementSpeed);
	
	PlaneDirection.X = MovementSpeed;
}

void APawnPlane::RotateRight(float Value)
{
	if ((Value > 0.f || Value < 0.f) && MovementSpeed != 0.f)
	{
		bRotatingPlane = true;

		TargetYawRotation += RotationRate * Value;

		TargetYawRotation = FMath::Clamp(TargetYawRotation, -360.f, 360.f);
	}
}

void APawnPlane::FlyUp(float Value)
{
	if (MovementSpeed > MinimumSpeedToFly && Value != 0.f)
	{
		bFlying = true;
		PlaneState = EPlaneState::EPS_Fly;
		PlaneDirection.Z += FlyRate * Value;
		PlaneDirection.Z = FMath::Clamp<float>(PlaneDirection.Z, MaximumHighness * -1.f, MaximumHighness);

		TargetPitchRotation = PlaneDirection.Z / 20.f;
	}
}

void APawnPlane::PlaneAccelerate(float Delta)
{
	UE_LOG(LogTemp, Warning, TEXT("%f - %f"), MovementSpeed, PlaneDirection.Z);
	FVector Vector = PlaneDirection;
	FHitResult Hit;
	float DefaultVectorZ = .2f * Delta;

	if (PlaneState == EPlaneState::EPS_Falling)
	{
		if (Gravity >= 0.f)
		{
			Gravity *= -1.f;
		}

		Vector.Z = Gravity * Delta;
		Vector.X = 8.f;
		bFlying = false;
		TargetPitchRotation = -20.f;

		if (MovementSpeed > MinimumSpeedToFly)
		{
			PlaneState = EPlaneState::EPS_Fly;
			TargetPitchRotation = 0.f;
			Vector.Z = DefaultVectorZ;
		}
		AddPlaneLocalOffset(Vector, &Hit);
	}
	else if (MovementSpeed > 0.f && PlaneState != EPlaneState::EPS_Falling)
	{
		Vector.X *= Delta;
		Vector.Y *= Delta;
		if (bFlying && MovementSpeed > MinimumSpeedToFly)
		{
			Vector.Z *= Delta;
			if (bCallFlyTimer)
			{
				bCallFlyTimer = false;
				GetWorld()->GetTimerManager().SetTimer(FlyTimerHandle, this, &APawnPlane::SetFlyToFalse, 3.f, false);
			}
		}
		else
		{
			Vector.Z = DefaultVectorZ;
			//Vector.Z = 0.1f;
		}

		if (MovementSpeed < MinimumSpeedToFly && PlaneState == EPlaneState::EPS_Fly)
		{
			PlaneState = EPlaneState::EPS_Falling;

			bFlying = false;
			if (Gravity >= 0.f)
			{
				Gravity *= -1.f;
	
			}

			Vector.Z = Gravity * Delta;
			Vector.X = 0.f;
		}

		AddPlaneLocalOffset(Vector, &Hit);
	}
	
}

void APawnPlane::ReleaseRotation()
{
	bRotatingPlane = false;
}

void APawnPlane::ReleaseFly()
{
	bFlying = false;
}

void APawnPlane::AddPlaneLocalOffset(FVector Location, FHitResult* HitResult)
{
	AddActorLocalOffset(Location, true, HitResult);
	if (HitResult->GetActor())
	{
		AWall* WallHitted = Cast<AWall>(HitResult->GetActor());
		if (WallHitted)
		{
			// Place Particle Here

			// Play Sound Here

			// Handle Game Over, Back to Menu / Quest chooser, Gold -- for killing innoncent ppl
			SetGameOver(false);
		}

		AActor* TheMesh = Cast<AActor>(HitResult->GetActor());
		//UStaticMeshComponent* TheMesh = Cast<UStaticMeshComponent>(HitResult->GetActor());
		if (TheMesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("OnLan"));
			PlaneState = EPlaneState::EPS_OnLand;
			TargetPitchRotation = 0.f;
			PlaneDirection.Z = 0.1f;
		}
	}
}

void APawnPlane::SetFlyToFalse()
{
	bFlying = false;
	PlaneDirection.Z = 0.f;
	GetWorld()->GetTimerManager().ClearTimer(FlyTimerHandle);
	bCallFlyTimer = true;
}

void APawnPlane::AddPlanePointByValue(int32 Value)
{
	PlanePoint += Value;
}

float APawnPlane::GetPlaneLocationZ()
{
	return GetActorLocation().Z - DefaultZLocation;
}

void APawnPlane::SetGameOver(bool bValue)
{
	bGameEnd = true;
	if (bValue)
	{
		//Win
		PlaneDirection = FVector(0.f);

		if (PlaneController)
		{
			PlaneController->SetGameOver(true);
		}
	}
	else
	{
		//lose
		SetActorHiddenInGame(true);
		if (PlaneController)
		{
			PlaneController->SetGameOver(false);
		}
	}
}

/**
* Getter n Setter
*/

void APawnPlane::SetPlanePoint(int32 Point)
{
	PlanePoint = Point;
}

int32 APawnPlane::GetPlanePoint()
{
	return PlanePoint;
}

void APawnPlane::SetPlaneMovementSpeed(float Speed)
{
	MovementSpeed = Speed;
}

float APawnPlane::GetPlaneMovementSpeed()
{
	return MovementSpeed;
}

float APawnPlane::GetPlaneMaximumMovementSpeed()
{
	return MaximumMovementSpeed;
}

float APawnPlane::GetPlaneMinimumSpeedToFly()
{
	return MinimumSpeedToFly;
}

float APawnPlane::GetPlaneHighness()
{
	return PlaneDirection.Z;
}

float APawnPlane::GetPlaneMaximumHighness()
{
	return MaximumHighness;
}

