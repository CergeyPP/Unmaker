// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Health/ZR_HealthComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "ZR_ZombieCharacter.generated.h"

class UZR_ZombieAttackComponent;

UCLASS()
class ZOMBIERANGE_API AZR_ZombieCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AZR_ZombieCharacter();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UZR_ZombieAttackComponent* AttackComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FName MainHandSocketName;

	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviourTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* DefaultAttackAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* PowerAttackAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	UZR_HealthComponent* HealthComponent;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

private:

	void OnDeathHandle();

	void InitAnimations();
	FVector GetHandLocation();

	void OnAttack(USkeletalMeshComponent* MeshComp);
	void OnHugeAttack(USkeletalMeshComponent* MeshComp);
};
