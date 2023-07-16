// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZR_HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIERANGE_API UZR_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UZR_HealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetHealthPercentage() { return Health / MaxHealth; }

	FOnDeath OnDeath;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	bool bIsZombie;

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type type) override;

private:

	float Health;

	UFUNCTION()
	void OnTakeAnyDamagehandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser);
};
