// Fill out your copyright notice in the Description page of Project Settings.


#include "ZR_WeaponComponent.h"

// Sets default values for this component's properties
UZR_WeaponComponent::UZR_WeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UZR_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SpawnWeapon();
}

void UZR_WeaponComponent::EndPlay(EEndPlayReason::Type EndReason)
{
	CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentWeapon->Destroy();

	Super::EndPlay(EndReason);
}


// Called every frame
void UZR_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UZR_WeaponComponent::SetWeaponSocket(USceneComponent* socket)
{
	WeaponSocket = socket;
}

void UZR_WeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;
	FActorSpawnParameters SpawnParametrs;
	SpawnParametrs.Owner = GetOwner();
	for (auto WeaponClass : WeaponClasses) {
		auto Weapon = GetWorld()->SpawnActor<AZR_BaseWeapon>(WeaponClass, SpawnParametrs);

		if (Weapon && WeaponSocket) {
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(WeaponSocket, AttachmentRules);
		}

		Weapon->SetActorHiddenInGame(true);
		Weapons.Add(Weapon);
	}
	Equip(0);
}

void UZR_WeaponComponent::StartFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}

void UZR_WeaponComponent::Reload()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->Reload();
}

void UZR_WeaponComponent::Equip(int32 WeaponIndex)
{
	if (Weapons.Num() == 0) return;
	auto Weapon = Weapons[WeaponIndex];
	if (Weapon && Weapon != CurrentWeapon)
	{
		UnEquip();
		CurrentWeapon = Weapon;
		CurrentWeapon->Equip();
		CurrentWeapon->SetActorHiddenInGame(false);
	}
}

void UZR_WeaponComponent::UnEquip()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->unEquip();
		CurrentWeapon->SetActorHiddenInGame(true);
		CurrentWeapon = nullptr;
	}
}

const FAmmoData UZR_WeaponComponent::GetCurrentWeaponAmmoData() const
{
	if (!CurrentWeapon) return FAmmoData();

	return CurrentWeapon->GetAmmoData();
}

void UZR_WeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}