// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI/ZR_ZombieSightComponent.h"

#include "ZR_AIController.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIERANGE_API AZR_AIController : public AAIController
{
	GENERATED_BODY()
public:

	AZR_AIController();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		UZR_ZombieSightComponent* SightComponent;

	void OnPossess(APawn* InPawn) override;
	
public:

	void Tick(float delta) override;
	void StartAttack();
	void StopAttack();
	bool CanAttack();
};
