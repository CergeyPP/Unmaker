// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZR_ZombieCharacter.h"

#include "ZR_ZombieAttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIERANGE_API UZR_ZombieAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZR_ZombieAttackComponent();

protected:


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float DefaultAttackDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float DefaultAttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float PowerAttackDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float PowerAttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float AttackPeriod;
	
	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartAttack();
	void StopAttack();

	void SelectAttack();

	void MakeDefaultAttack();
	void MakeHugeAttack();

	void OnAttackDealt();
	void OnPowerAttackDealt();

	bool CanAttack();

private:

	AZR_ZombieCharacter* Character;

	bool bCanAttack;
	FTimerHandle AttackTimer;

};
