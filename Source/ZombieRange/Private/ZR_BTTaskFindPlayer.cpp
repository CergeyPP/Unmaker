// Fill out your copyright notice in the Description page of Project Settings.


#include "ZR_BTTaskFindPlayer.h"
#include "Enemies/Public/ZR_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Enemies/Public/ZR_ZombieAttackComponent.h"

UZR_BTTaskFindPlayer::UZR_BTTaskFindPlayer()
{
	NodeName = "Find Player";
	bIsAttacking = false;
}

EBTNodeResult::Type UZR_BTTaskFindPlayer::ExecuteTask(UBehaviorTreeComponent& BTree, uint8* NodeMemory)
{
	const auto Controller = BTree.GetAIOwner();
	const auto Blackboard = BTree.GetBlackboardComponent();

	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if (!NavSys) return EBTNodeResult::Failed;

	const auto ZombieController = Cast<AZR_AIController>(Controller);
	if (!ZombieController) return EBTNodeResult::Failed;

	const AActor* target = Cast<AActor>(Blackboard->GetValueAsObject(AttackTargetKey.SelectedKeyName));

	if (!target) 
	{
		ZombieController->StopAttack();
		return EBTNodeResult::Failed;
	}
	if (!ZombieController->CanAttack() && bIsAttacking)
	{
		return EBTNodeResult::InProgress;
	}

	if (ZombieController->CanAttack() && !bIsAttacking)
	{
		ZombieController->StartAttack();
		bIsAttacking = true;
		return EBTNodeResult::InProgress;
	}

	if (ZombieController->CanAttack() && bIsAttacking)
	{
		bIsAttacking = false;
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
	
	/*FVector playerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FNavLocation location;
	const auto Found = NavSys->GetRandomReachablePointInRadius(playerLocation, 100.f, location);
	if (!Found) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(PlayerLocationKey.SelectedKeyName, location.Location);*/

	//return EBTNodeResult::Succeeded;
}
