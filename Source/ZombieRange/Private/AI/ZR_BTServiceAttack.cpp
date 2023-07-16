// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ZR_BTServiceAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/Public/ZR_AIController.h"
#include "Enemies/Public/ZR_ZombieAttackComponent.h"

UZR_BTServiceAttack::UZR_BTServiceAttack()
{
	NodeName = "Attack";
}

void UZR_BTServiceAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController && Controller)
		{
			const auto AttackComponent = Cast<UZR_ZombieAttackComponent>(Controller->GetPawn()->GetComponentByClass(UZR_ZombieAttackComponent::StaticClass()));
			const auto Player = Cast<AActor>(Blackboard->GetValueAsObject(AttackTargetKey.SelectedKeyName));
			
			if (AttackComponent)
				Player ? AttackComponent->StartAttack() : AttackComponent->StopAttack();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
