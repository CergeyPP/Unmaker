// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ZR_PlayerHUDWidget.h"
#include "ZR_NewWaveWidget.h"
#include "ZombieRange/ZombieRangeGameModeBase.h"

#include "ZR_HUD.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIERANGE_API AZR_HUD : public AHUD
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> GameOverWidgetClass;

	void OnGameStateChangedHandle(EGameState State);

public:

	void BeginPlay() override;

private:

	UPROPERTY()
	TMap<EGameState, UUserWidget*> GameWidgets;

	UUserWidget* CurrentWidget = nullptr;
};
