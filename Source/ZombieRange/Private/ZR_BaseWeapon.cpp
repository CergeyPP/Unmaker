// Fill out your copyright notice in the Description page of Project Settings.


#include "ZR_BaseWeapon.h"
#include "Animations/ZR_ReloadNotify.h"
#include "ZR_MainCharacter.h"

// Sets default values
AZR_BaseWeapon::AZR_BaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(SkeletalMesh);

	VFXComponent = CreateDefaultSubobject<UZR_VFXWeaponComponent>("VFX Component");
}

// Called when the game starts or when spawned
void AZR_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmoData = AmmoData;
	OnReloadFinished();
	InitAnimations();

	UE_LOG(LogTemp, Warning, TEXT("Ammo In Magazine: %i, Max Ammo In Magazine: %i, Ammo Capacity : % i"), 
		CurrentAmmoData.BulletInMagazine, 
		CurrentAmmoData.MaxBulletsInMagazine, 
		CurrentAmmoData.BulletCapacity
	);
}

// Called every frame
void AZR_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

EWeaponType AZR_BaseWeapon::Type()
{
	return type;
}

void AZR_BaseWeapon::MakeShot()
{
	if (CurrentAmmoData.BulletInMagazine > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire!"));
		PlayAnimMontage(FireAnimMontage);
		for (int32 i = 0; i < HitsCount; i++)
			MakeHit();

		CurrentAmmoData.BulletInMagazine--;
	}
	else
	{
		Reload();
	}
}

void AZR_BaseWeapon::MakeHit()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	APlayerController* PlayerController = Character->GetController<APlayerController>();
	if (!PlayerController) return;

	FVector ViewLocation;
	FRotator ViewRotation;
	PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);

	FVector TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(accuracyRadius);
	FVector TraceEnd = ViewLocation + FMath::VRandCone(ViewRotation.Vector(), HalfRad) * ShootRange;


	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult,
		TraceStart,
		TraceEnd,
		ECC_Visibility
	);

	if (HitResult.bBlockingHit)
	{
		if (HitResult.GetActor()) {
			FDamageEvent DamageEvent(UDamageType::StaticClass());
			HitResult.GetActor()->TakeDamage(Damage, DamageEvent, PlayerController, Character);
		}

		VFXComponent->PlayImpactVFX(HitResult);
	}
}

void AZR_BaseWeapon::StartFire()
{
	if (isReloading || !canShoot) return;
	MakeShot();

	canShoot = false;
	GetWorldTimerManager().SetTimer(ShootTimer, this, &AZR_BaseWeapon::OnShootPeriodEnd, ShootPeriod, !bIsShootsOnce);
}

void AZR_BaseWeapon::StopFire()
{
	if (!bIsShootsOnce)
	{
		canShoot = true;
		GetWorldTimerManager().ClearTimer(ShootTimer);
	}
}

void AZR_BaseWeapon::Reload()
{
	if (isReloading) return;
	if (CurrentAmmoData.BulletInMagazine == CurrentAmmoData.MaxBulletsInMagazine) return;

	if (!CurrentAmmoData.bIsInfiniteBullets && CurrentAmmoData.BulletCapacity == 0) return;

	isReloading = true;
	if (!CurrentAmmoData.bIsInfiniteBullets)
	{
		CurrentAmmoData.BulletCapacity += CurrentAmmoData.BulletInMagazine;
		CurrentAmmoData.BulletInMagazine = 0;
	}
	GetWorldTimerManager().ClearTimer(ShootTimer);
	StopAllAnimMontages();
	PlayAnimMontage(ReloadAnimMontage);
}

const FAmmoData AZR_BaseWeapon::GetAmmoData() const
{
	return CurrentAmmoData;
}

void AZR_BaseWeapon::PlayAnimMontage(UAnimMontage* Montage)
{
	const auto AnimInstance = SkeletalMesh->GetAnimInstance();
	if (!AnimInstance) return;

	AnimInstance->Montage_Play(Montage);
}

void AZR_BaseWeapon::StopAllAnimMontages() 
{
	const auto AnimInstance = SkeletalMesh->GetAnimInstance();
	if (!AnimInstance) return;

	AnimInstance->StopAllMontages(false);
}

void AZR_BaseWeapon::Equip()
{
}

void AZR_BaseWeapon::unEquip()
{
	StopAllAnimMontages();
	StopFire();
	isReloading = false;
}

void AZR_BaseWeapon::InitAnimations()
{
	if (!ReloadAnimMontage) return;
	const auto Notifies = ReloadAnimMontage->Notifies;

	for (auto NotifyEvent : Notifies)
	{
		UZR_ReloadNotify* event = Cast<UZR_ReloadNotify>(NotifyEvent.Notify);
		if (event)
		{
			event->onNotified.AddUObject(this, &AZR_BaseWeapon::OnReloadFinished);
			break;
		}
	}
}

void AZR_BaseWeapon::OnReloadFinished()
{
	isReloading = false;
	if (bIsShootsOnce)
		canShoot = true;
	if (CurrentAmmoData.bIsInfiniteBullets)
	{
		CurrentAmmoData.BulletInMagazine = CurrentAmmoData.MaxBulletsInMagazine;
	}
	else
	{
		int32 NewBulletsInMagazine = FMath::Clamp(CurrentAmmoData.BulletCapacity, 0, CurrentAmmoData.MaxBulletsInMagazine);
		CurrentAmmoData.BulletInMagazine = NewBulletsInMagazine;
		CurrentAmmoData.BulletCapacity -= NewBulletsInMagazine;
	}
}

void AZR_BaseWeapon::OnShootPeriodEnd()
{
	canShoot = true;
	if (!bIsShootsOnce)
	{
		MakeShot();
		canShoot = false;
	}
	else
		GetWorldTimerManager().ClearTimer(ShootTimer);
}
