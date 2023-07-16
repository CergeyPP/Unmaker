// Fill out your copyright notice in the Description page of Project Settings.


#include "ZR_PlayerController.h"
#include "ZombieRange/ZombieRangeGameModeBase.h"

void AZR_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld()) return;

	if (!GetWorld()->GetAuthGameMode()) return;

	const auto GameMode = Cast<AZombieRangeGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->OnGameStateChanged.AddUObject(this, &AZR_PlayerController::OnGameStateChanged);
}

void AZR_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Pause", IE_Pressed, this, &AZR_PlayerController::OnPauseGame);
}

void AZR_PlayerController::OnPauseGame()
{
	if (!GetWorld()) return;

	if (!GetWorld()->GetAuthGameMode()) return;

	const auto GameMode = Cast<AZombieRangeGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	if (GameMode->IsPaused())
	{
		GameMode->ClearPause();
	}
	else
	{
		GameMode->SetPause(this);
	}
}

void AZR_PlayerController::OnGameStateChanged(EGameState State)
{
	if (State == EGameState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}
