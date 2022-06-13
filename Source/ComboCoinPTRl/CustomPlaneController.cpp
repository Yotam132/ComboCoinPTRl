// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlaneController.h"


#include "Blueprint/UserWidget.h"
#include "GameFramework/Pawn.h"
#include "PawnPlane.h"
#include "kismet/GameplayStatics.h"

ACustomPlaneController::ACustomPlaneController()
{
	PointAsset = nullptr;
	PointHUD = nullptr;
	PossessedPawn = nullptr;
}

void ACustomPlaneController::BeginPlay()
{
	Super::BeginPlay();

	PossessedPawn = Cast<APawnPlane>(UGameplayStatics::GetPlayerPawn(this, 0));

	PointHUD = CreateCustomWidget(PointAsset);
	if (PointHUD)
	{
		PointHUD->AddToViewport();
		PointHUD->SetVisibility(ESlateVisibility::Visible);
	}

	MovementSpeedHUD = CreateCustomWidget(MovementSpeedAsset);
	if (MovementSpeedHUD)
	{
		MovementSpeedHUD->AddToViewport();
		MovementSpeedHUD->SetVisibility(ESlateVisibility::Visible);
	}

	HighnessHUD = CreateCustomWidget(HighnessAsset);
	if (MovementSpeedHUD)
	{
		HighnessHUD->AddToViewport();
		HighnessHUD->SetVisibility(ESlateVisibility::Visible);
	}
}

UUserWidget* ACustomPlaneController::CreateCustomWidget(TSubclassOf<UUserWidget> Widget)
{
	if (Widget)
	{
		return CreateWidget<UUserWidget>(this, Widget);
	}
	return nullptr;
}

void ACustomPlaneController::SetGameOver(bool bWin)
{
	FInputModeUIOnly Input;
	SetInputMode(Input);
	
	bShowMouseCursor = true;
	HighnessHUD->SetVisibility(ESlateVisibility::Hidden);
	MovementSpeedHUD->SetVisibility(ESlateVisibility::Hidden);
	PointHUD->SetVisibility(ESlateVisibility::Hidden);
	
	if (bWin)
	{
		// Player Win
		UE_LOG(LogTemp, Warning, TEXT("Player Win"));
		GameOverHUD = CreateCustomWidget(GameOverWinAsset);
	}
	else
	{
		// Player Lose
		UE_LOG(LogTemp, Warning, TEXT("Player Lose"));
		GameOverHUD = CreateCustomWidget(GameOverLoseAsset);
	}

	if (GameOverHUD)
	{
		GameOverHUD->AddToViewport();
		
		GameOverHUD->SetVisibility(ESlateVisibility::Visible);
	}
}

