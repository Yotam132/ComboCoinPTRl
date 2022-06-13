// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/Pawn.h"
#include "kismet/GameplayStatics.h"

AComboPlayerController::AComboPlayerController()
{
	CoinAsset = nullptr;
	PointHUD = nullptr;
	PossessedPawn = nullptr;
}

void AComboPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PossessedPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	PointHUD = CreateCustomWidget(CoinAsset);
	if(PointHUD)
	{
		PointHUD->AddToViewport();
		PointHUD->SetVisibility(ESlateVisibility::Visible);
	}
}

UUserWidget* AComboPlayerController::CreateCustomWidget(TSubclassOf<UUserWidget> Widget)
{
	if(Widget)
	{
		return CreateWidget<UUserWidget>(this, Widget);
	}
	return nullptr;
}
