// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Public/ZR_ZombieAttackComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Health/ZR_ZombieDamageType.h"

UZR_ZombieAttackComponent::UZR_ZombieAttackComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}



void UZR_ZombieAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AZR_ZombieCharacter>(GetOwner());
	check(Character);
	bCanAttack = true;
}



void UZR_ZombieAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UZR_ZombieAttackComponent::StartAttack()
{
	if (!CanAttack()) return;
	SelectAttack();
	GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &UZR_ZombieAttackComponent::StopAttack, AttackPeriod, true);
}

void UZR_ZombieAttackComponent::StopAttack()
{
	bCanAttack = true;
	GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
}

void UZR_ZombieAttackComponent::MakeDefaultAttack()
{
	bCanAttack = false;
	Character->PlayAnimMontage(Character->DefaultAttackAnimMontage);
}

void UZR_ZombieAttackComponent::SelectAttack()
{
	bool isAttackDefault = (bool)(FMath::Rand() % 5);
	isAttackDefault ? MakeDefaultAttack() : MakeHugeAttack();
}

bool UZR_ZombieAttackComponent::CanAttack()
{
	return bCanAttack;
}

void UZR_ZombieAttackComponent::MakeHugeAttack()
{
	//Character->bBlockInput = true;
	bCanAttack = false;
	Character->PlayAnimMontage(Character->PowerAttackAnimMontage);
}

void UZR_ZombieAttackComponent::OnAttackDealt()
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	float collisionRadius = Pawn->GetSimpleCollisionRadius();

	FVector DamageLocation = Pawn->GetActorLocation() + Pawn->GetActorForwardVector() * (collisionRadius + DefaultAttackRange / 2);
	float DamageRadius = DefaultAttackRange / 2;

	UGameplayStatics::ApplyRadialDamage(GetWorld(),
		DefaultAttackDamage,
		DamageLocation,
		DamageRadius,
		UZR_ZombieDamageType::StaticClass(),
		{ GetOwner() },
		GetOwner(),
		nullptr,
		true
	);

	//DrawDebugSphere(GetWorld(), DamageLocation, DamageRadius, 24, FColor::Blue, false, 40.f);

	//Character->bBlockInput = false;
}

void UZR_ZombieAttackComponent::OnPowerAttackDealt()
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	float collisionRadius = Pawn->GetSimpleCollisionRadius();

	FVector DamageLocation = Pawn->GetActorLocation() + Pawn->GetActorForwardVector() * (collisionRadius + PowerAttackRange / 2);
	float DamageRadius = PowerAttackRange / 2;

	UGameplayStatics::ApplyRadialDamage(GetWorld(),
		PowerAttackDamage,
		DamageLocation,
		DamageRadius,
		UZR_ZombieDamageType::StaticClass(),
		{ GetOwner() },
		GetOwner(),
		nullptr,
		true
	);

	//DrawDebugSphere(GetWorld(), DamageLocation, DamageRadius, 24, FColor::Red, false, 10.f);
	
	//Character->bBlockInput = false;
}

