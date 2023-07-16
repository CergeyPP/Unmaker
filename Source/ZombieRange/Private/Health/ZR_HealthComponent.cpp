// Fill out your copyright notice in the Description page of Project Settings.


#include "Health/ZR_HealthComponent.h"
#include "Health/ZR_ZombieDamageType.h"


UZR_HealthComponent::UZR_HealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

float UZR_HealthComponent::GetHealth()
{
	return Health;
}

void UZR_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	//check(MaxHealth <= 0);
	Health = MaxHealth;

	AActor* Owner = GetOwner();
	if (Owner) {
		FScriptDelegate delegate;
		delegate.BindUFunction(this, "OnTakeAnyDamagehandle");
		Owner->OnTakeAnyDamage.Add(delegate);
	}
}

void UZR_HealthComponent::EndPlay(EEndPlayReason::Type type)
{
	if (!IsDead())
		OnDeath.Broadcast();

	Super::EndPlay(type);
}

bool UZR_HealthComponent::IsDead()
{
	return FMath::IsNearlyZero(Health);
}

float UZR_HealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

void UZR_HealthComponent::OnTakeAnyDamagehandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	const auto ZombieDamageType = Cast<UZR_ZombieDamageType>(DamageType);
	if (bIsZombie && ZombieDamageType) return;

	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
	if (IsDead())
		OnDeath.Broadcast();
}

