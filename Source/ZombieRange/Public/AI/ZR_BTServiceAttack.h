// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ZR_BTServiceAttack.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIERANGE_API UZR_BTServiceAttack : public UBTService
{
	GENERATED_BODY()

public:
	UZR_BTServiceAttack();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector AttackTargetKey;

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
