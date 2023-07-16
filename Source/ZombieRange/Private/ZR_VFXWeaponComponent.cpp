// Fill out your copyright notice in the Description page of Project Settings.


#include "ZR_VFXWeaponComponent.h"


UZR_VFXWeaponComponent::UZR_VFXWeaponComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UZR_VFXWeaponComponent::PlayImpactVFX(const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}



