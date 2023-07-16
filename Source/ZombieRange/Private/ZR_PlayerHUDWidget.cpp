// Fill out your copyright notice in the Description page of Project Settings.


#include "ZR_PlayerHUDWidget.h"
#include "ZombieRange/ZombieRangeGameModeBase.h"


float UZR_PlayerHUDWidget::GetHealthPercent() const
{
	UZR_HealthComponent* HealthComponent = GetPlayerComponent<UZR_HealthComponent>();
	if (!HealthComponent) return 0.f;

	return HealthComponent->GetHealthPercentage();
}

float UZR_PlayerHUDWidget::GetHealth() const
{
	UZR_HealthComponent* HealthComponent = GetPlayerComponent<UZR_HealthComponent>();
	if (!HealthComponent) return 0.f;

	return HealthComponent->GetHealth();
}

float UZR_PlayerHUDWidget::GetMaxHealth() const
{
	UZR_HealthComponent* HealthComponent = GetPlayerComponent<UZR_HealthComponent>();
	if (!HealthComponent) return 0.f;

	return HealthComponent->GetMaxHealth();
}

const FAmmoData UZR_PlayerHUDWidget::GetWeaponAmmoData() const
{
	auto WeaponComponent = GetPlayerComponent<UZR_WeaponComponent>();
	if (!WeaponComponent) return FAmmoData();

	return WeaponComponent->GetCurrentWeaponAmmoData();
}

bool UZR_PlayerHUDWidget::IsPlayerAlive() const
{
	UZR_HealthComponent * HealthComponent = GetPlayerComponent<UZR_HealthComponent>();
	
	return HealthComponent && !HealthComponent->IsDead();
}

int32 UZR_PlayerHUDWidget::GetPlayerScore() const
{
	if (!GetWorld()) return 0;

	const auto GameMode = Cast<AZombieRangeGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return 0;

	return GameMode->GetPlayerScore();
}
