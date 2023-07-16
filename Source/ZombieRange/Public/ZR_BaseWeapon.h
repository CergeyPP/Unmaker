// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "ZR_VFXWeaponComponent.h"


#include "ZR_BaseWeapon.generated.h"

UENUM()
enum class EWeaponType {
	Glock20,
	Remington,
};

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 BulletInMagazine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxBulletsInMagazine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 BulletCapacity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsInfiniteBullets;
};

UCLASS()
class ZOMBIERANGE_API AZR_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AZR_BaseWeapon();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EWeaponType type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* FireAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* ReloadAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UZR_VFXWeaponComponent* VFXComponent;
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UNiagaraSystem* MuzzleFX;*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		FName MuzzleSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
		int32 HitsCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
		float accuracyRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float ShootPeriod;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float ShootRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	bool bIsShootsOnce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	FAmmoData AmmoData;

	//UNiagaraComponent* 

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EWeaponType Type();
	virtual void StartFire();
	virtual void StopFire();
	void Reload();

	const FAmmoData GetAmmoData() const;
	void StopAllAnimMontages();

	void Equip();
	void unEquip();

private:

	FTimerHandle ShootTimer;
	FAmmoData CurrentAmmoData;
	bool isReloading = false;
	bool canShoot = true;

	void MakeShot();
	void MakeHit();

	void PlayAnimMontage(UAnimMontage* Montage);


	void InitAnimations();
	void OnReloadFinished();
	void OnShootPeriodEnd();
};
