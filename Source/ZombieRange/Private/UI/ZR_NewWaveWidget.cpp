// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ZR_NewWaveWidget.h"
#include "ZombieRange/ZombieRangeGameModeBase.h"

bool UZR_NewWaveWidget::IsNewWaveOccuried() const
{
	if (!GetWorld())
		return false;

	const auto GameMode = Cast<AZombieRangeGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return false;

	return GameMode->IsNewWaveComing();
}

void UZR_NewWaveWidget::OnNewWaveHandle()
{
	bIsNewWave = true;
	GetWorld()->GetTimerManager().SetTimer(AnnounceFadeTimer, this, &UZR_NewWaveWidget::TurnWidgetOff, 3.f, false);
}

void UZR_NewWaveWidget::TurnWidgetOff()
{
	bIsNewWave = false;
}
