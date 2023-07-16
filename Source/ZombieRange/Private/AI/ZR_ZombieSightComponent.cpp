// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ZR_ZombieSightComponent.h"
#include "Perception/AISense_Sight.h"
#include "Enemies/Public/ZR_AIController.h"

AActor* UZR_ZombieSightComponent::GetPlayerToAttack()
{
	TArray<AActor*> PercievedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercievedActors);

	if (PercievedActors.Num() == 0) return nullptr;
	const auto Controller = Cast<AZR_AIController>(GetOwner());

	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	const AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!Player) return nullptr;

	for (auto Actor : PercievedActors)
		if (Actor == Player)
			return Actor;

	return nullptr;
}
