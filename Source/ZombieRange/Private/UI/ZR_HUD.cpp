// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ZR_HUD.h"

void AZR_HUD::OnGameStateChangedHandle(EGameState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
	//UE_LOG(LogTemp, Warning, TEXT("New gameState: %s"), *UEnum::GetValueAsString(State));
}

void AZR_HUD::BeginPlay()
{
	auto PlayerHUD = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);

	auto PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);

	auto GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);

	GameWidgets.Add(EGameState::InProgress, PlayerHUD);
	GameWidgets.Add(EGameState::Pause, PauseWidget);
	GameWidgets.Add(EGameState::GameOver, GameOverWidget);

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto Widget = GameWidgetPair.Value;
		if (!Widget) continue;

		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}

	const auto GameMode = Cast<AZombieRangeGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->OnGameStateChanged.AddUObject(this, &AZR_HUD::OnGameStateChangedHandle);
	}

	CurrentWidget = nullptr;
}
