// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ComboPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class COMBOCOINPTRL_API AComboPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AComboPlayerController();

	virtual void BeginPlay() override;

	/** HUD Asset */
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> CoinAsset;

	/** HUD Class */
	UPROPERTY(VisibleAnywhere, Category = "HUD")
	UUserWidget* CoinHUD;

private:
	UUserWidget* CreateCustomWidget(TSubclassOf<UUserWidget> Widget);
};
