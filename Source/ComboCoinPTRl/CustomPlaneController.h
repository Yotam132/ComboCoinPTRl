// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlaneController.generated.h"

/**
 * 
 */
UCLASS()
class COMBOCOINPTRL_API ACustomPlaneController : public APlayerController
{
	GENERATED_BODY()

public:
	ACustomPlaneController();

	virtual void BeginPlay() override;

	/** 
	* Function that called when the game is over, whether its win or lose
	* 
	* @param bWin - if True then win, else Lose
	*/
	void SetGameOver(bool bWin);

	/** HUD Asset */
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> PointAsset;

	/** HUD Class */
	UPROPERTY(VisibleAnywhere, Category = "HUD")
	UUserWidget* PointHUD;

	/** HUD Asset */
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> MovementSpeedAsset;

	/** HUD Class */
	UPROPERTY(VisibleAnywhere, Category = "HUD")
	UUserWidget* MovementSpeedHUD;

	/** HUD Asset */
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> HighnessAsset;

	/** HUD Class */
	UPROPERTY(VisibleAnywhere, Category = "HUD")
	UUserWidget* HighnessHUD;
	
	/** HUD Asset */
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> GameOverWinAsset;

	/** HUD Asset */
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> GameOverLoseAsset;

	/** HUD Class */
	UPROPERTY(VisibleAnywhere, Category = "HUD")
	UUserWidget* GameOverHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controllers")
	class APawnPlane* PossessedPawn;

private:

	UUserWidget* CreateCustomWidget(TSubclassOf<UUserWidget> Widget);
	
};
