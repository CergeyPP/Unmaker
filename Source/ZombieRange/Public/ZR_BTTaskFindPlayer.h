// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ZR_BTTaskFindPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIERANGE_API UZR_BTTaskFindPlayer : public UBTTaskNode
{
	GENERATED_BODY()
public:

	UZR_BTTaskFindPlayer();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& BTree, uint8* NodeMemory);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector AttackTargetKey;

private:
	bool bIsAttacking;
};
