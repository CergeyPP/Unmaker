// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Public/ZR_AIController.h"
#include "Enemies/Public/ZR_ZombieCharacter.h"
#include "Enemies/Public/ZR_ZombieAttackComponent.h"

AZR_AIController::AZR_AIController()
{
	SightComponent = CreateDefaultSubobject<UZR_ZombieSightComponent>("SightComponent");
	SetPerceptionComponent(*SightComponent);
}

void AZR_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto Zombie = Cast<AZR_ZombieCharacter>(InPawn);
	if (!Zombie) return;

	RunBehaviorTree(Zombie->BehaviourTree);
}

void AZR_AIController::Tick(float delta)
{
	Super::Tick(delta);

	SetFocus(SightComponent->GetPlayerToAttack());
}

void AZR_AIController::StartAttack()
{
	const auto Zombie = Cast<AZR_ZombieCharacter>(GetPawn());
	if (!Zombie) return;

	const auto AttackComponent = Cast<UZR_ZombieAttackComponent>(Zombie->GetComponentByClass(UZR_ZombieAttackComponent::StaticClass()));
	if (!AttackComponent) return;

	AttackComponent->StartAttack();
}

void AZR_AIController::StopAttack()
{
	const auto Zombie = Cast<AZR_ZombieCharacter>(GetPawn());
	if (!Zombie) return;

	const auto AttackComponent = Cast<UZR_ZombieAttackComponent>(Zombie->GetComponentByClass(UZR_ZombieAttackComponent::StaticClass()));
	if (!AttackComponent) return;

	AttackComponent->StopAttack();
}

bool AZR_AIController::CanAttack()
{
	const auto Zombie = Cast<AZR_ZombieCharacter>(GetPawn());
	if (!Zombie) return false;

	const auto AttackComponent = Cast<UZR_ZombieAttackComponent>(Zombie->GetComponentByClass(UZR_ZombieAttackComponent::StaticClass()));
	if (!AttackComponent) return false;

	return AttackComponent->CanAttack();
}