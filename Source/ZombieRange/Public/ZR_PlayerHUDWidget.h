// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Health/ZR_HealthComponent.h"
#include "ZR_WeaponComponent.h"
#include "ZR_PlayerHUDWidget.generated.h"

UCLASS()
class ZOMBIERANGE_API UZR_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		const FAmmoData GetWeaponAmmoData() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
		int32 GetPlayerScore() const;

private:


	template<typename T>
	T* GetPlayerComponent() const {
		const auto Player = GetOwningPlayerPawn();
		if (!Player) return nullptr;

		const auto Component = Cast<T>(Player->GetComponentByClass(T::StaticClass()));
		return Component;
	}
};
