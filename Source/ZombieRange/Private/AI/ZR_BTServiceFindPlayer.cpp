// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ZR_BTServiceFindPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/Public/ZR_AIController.h"
#include "Health/ZR_HealthComponent.h"

UZR_BTServiceFindPlayer::UZR_BTServiceFindPlayer()
{
	NodeName = "Find Survivor";
}

void UZR_BTServiceFindPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard) 
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController && Controller)
		{
			const auto Player = PlayerController->GetPawn();
			if (Player) {
				Blackboard->SetValueAsObject(PlayerSelectorKey.SelectedKeyName, Player);

				const auto Health = Cast<UZR_HealthComponent>(Player->GetComponentByClass(UZR_HealthComponent::StaticClass()));
				Blackboard->SetValueAsObject(AttackTargetKey.SelectedKeyName, Health && !Health->IsDead() ? Controller->GetFocusActor() : nullptr);
		
				/*float attackRange = AttackRange;
				float distanceToPlayer = (PlayerController->GetPawn()->GetActorLocation() - Controller->GetPawn()->GetActorLocation()).Length();
				if (distanceToPlayer <= attackRange)
				{

					if (GEngine)
						GEngine->AddOnScreenDebugMessage(0, 15.0f, FColor::Yellow, TEXT("Set AttackTarget!"));
					Blackboard->SetValueAsObject(AttackTargetKey.SelectedKeyName, PlayerController->GetPawn());
				}
				else
				{
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(0, 15.0f, FColor::Yellow, TEXT("UnSet AttackTarget!"));
					Blackboard->SetValueAsObject(AttackTargetKey.SelectedKeyName, nullptr);
				}
				*/

				//Controller->SetFocus(Player);
			}
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}