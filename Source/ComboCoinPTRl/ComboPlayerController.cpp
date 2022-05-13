// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboPlayerController.h"

#include "Blueprint/UserWidget.h"

AComboPlayerController::AComboPlayerController()
{
	CoinAsset = nullptr;
	CoinHUD = nullptr;
}

void AComboPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CoinHUD = CreateCustomWidget(CoinAsset);
	if(CoinHUD)
	{
		CoinHUD->AddToViewport();
		CoinHUD->SetVisibility(ESlateVisibility::Visible);
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
