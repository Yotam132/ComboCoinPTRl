// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CustomAIController.generated.h"

/**
 * 
 */
UCLASS()
class COMBOCOINPTRL_API ACustomAIController : public AAIController
{
	GENERATED_BODY()

public:
	/** Constructor */
	ACustomAIController();
	
	/** Begin Play */
	virtual void BeginPlay() override;

	/** Move To Next Follow Point */
	void MoveToFollowPoint();

	/** Get Next Follow Point */
	void GetNextFollowPoint();

	/** Set Possessing Char */
	void SetPossessingChar(class AComboCoinPTRlCharacter* TheChar);

	class AFollowPoint* GetNextPoint();

	AFollowPoint* GetLastPoint();

	void SetLastPoint(AFollowPoint* Point);

private:
	/** Next Follow Point */
	UPROPERTY(VisibleAnywhere, Category = "Debug")
	AFollowPoint* NextPoint;
	
	/** Last Follow Point */
	UPROPERTY(VisibleAnywhere, Category = "Debug")
	AFollowPoint* LastPoint;

	/** Possessing Character */
	UPROPERTY(VisibleAnywhere, Category = "Debug")
	class AComboCoinPTRlCharacter* Char;

	/** Sphere Radius */
	UPROPERTY(EditAnywhere, Category = "Sphere")
	float SphereRadius;

	/** Timer Manager */
	FTimerHandle TimerHandle;


	/** Function to call Move to target */
	void TimeredMoveToFollowPoint();
};


