// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZR_BaseWeapon.h"

#include "ZR_WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIERANGE_API UZR_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZR_WeaponComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndReason);

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AZR_BaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* WeaponSocket = nullptr;

	UPROPERTY()
	AZR_BaseWeapon* CurrentWeapon = nullptr;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetWeaponSocket(USceneComponent* socket);
	void SpawnWeapon();

	void StartFire();
	void StopFire();
	void Reload();

	void Equip(int32 WeaponIndex);
	void UnEquip();

	const FAmmoData GetCurrentWeaponAmmoData() const;

private:

	UPROPERTY();
	TArray<AZR_BaseWeapon*> Weapons;
};
