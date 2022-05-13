// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAIController.h"

#include "ComboCoinPTRlCharacter.h"
#include "DrawDebugHelpers.h"
#include "FollowPoint.h"
#include "Kismet/KismetSystemLibrary.h"

ACustomAIController::ACustomAIController()
{
	NextPoint = nullptr;
	LastPoint = nullptr;
	Char = nullptr;

	SphereRadius = 400.f;
}

void ACustomAIController::BeginPlay()
{
	Super::BeginPlay();

	GetNextFollowPoint();
}

void ACustomAIController::MoveToFollowPoint()
{
	if(!NextPoint)
	{
		GetNextFollowPoint();	
	}
	else if(NextPoint)
	{
		MoveToActor(NextPoint, 5.f, false, true, true);
	}
	else
	{
		GetNextFollowPoint();
	}
}

void ACustomAIController::GetNextFollowPoint()
{
	if(!Char)
	{
		return;
	}
	
	DrawDebugSphere(GetWorld(), Char->GetActorLocation() + Char->GetActorForwardVector() * 220.f , SphereRadius, 12, FColor::Green, false, 10.f, 0, 1.2f);


	TArray<FOverlapResult> OverlapResult;
	TArray<AFollowPoint*> FollowPointDetected;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(NextPoint);
	Params.AddIgnoredActor(LastPoint);
	
	GetWorld()->OverlapMultiByChannel(OverlapResult, Char->GetActorLocation() + Char->GetActorForwardVector() * 220.f, FQuat(FRotator(0.f)), ECollisionChannel::ECC_WorldDynamic, FCollisionShape::MakeSphere(SphereRadius), Params);

	if(OverlapResult.Num() > 0)
	{
		for(FOverlapResult Res : OverlapResult)
		{
			AFollowPoint* Point = Cast<AFollowPoint>(Res.GetActor());
			if(Point)
			{
				if(NextPoint != Point && LastPoint != Point)
				{
					// NextPoint = Point;
					// MoveToFollowPoint();
					// break;

					FollowPointDetected.Add(Point);
				}
			}
		}

		if(FollowPointDetected.Num() > 0)
		{
			uint8 RandIndex = FMath::RandRange(0, FollowPointDetected.Num() - 1);
			NextPoint = FollowPointDetected[RandIndex];
			MoveToFollowPoint();
		}
		else
		{
			if(LastPoint)
			{
				NextPoint = LastPoint;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACustomAIController::TimeredMoveToFollowPoint, 5.f, false);
			}
		}
	}
}

void ACustomAIController::TimeredMoveToFollowPoint()
{
	MoveToFollowPoint();
}

void ACustomAIController::SetPossessingChar(AComboCoinPTRlCharacter* TheChar)
{
	Char = TheChar;
}

AFollowPoint* ACustomAIController::GetNextPoint()
{
	return NextPoint;
}

AFollowPoint* ACustomAIController::GetLastPoint()
{
	return LastPoint;
}

void ACustomAIController::SetLastPoint(AFollowPoint* Point)
{
	LastPoint = Point;
}
