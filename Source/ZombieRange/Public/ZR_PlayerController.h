// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZombieRange/ZombieRangeGameModeBase.h"

#include "ZR_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIERANGE_API AZR_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void OnPauseGame();

	void OnGameStateChanged(EGameState State);
};
