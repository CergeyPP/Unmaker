// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "ZR_VFXWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIERANGE_API UZR_VFXWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZR_VFXWeaponComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UNiagaraSystem* Effect;

public:	

	void PlayImpactVFX(const FHitResult& Hit);
};
