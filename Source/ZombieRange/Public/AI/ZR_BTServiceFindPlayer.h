// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"


#include "ZR_BTServiceFindPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIERANGE_API UZR_BTServiceFindPlayer : public UBTService
{
	GENERATED_BODY()
	
public:
	UZR_BTServiceFindPlayer();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PlayerSelectorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector AttackTargetKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AttackRange;

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
