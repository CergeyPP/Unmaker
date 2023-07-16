// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "ZR_ZombieSightComponent.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIERANGE_API UZR_ZombieSightComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:

	AActor* GetPlayerToAttack();
};
