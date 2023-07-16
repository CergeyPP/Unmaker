// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Public/ZR_ZombieCharacter.h"
#include "Enemies/Public/ZR_AIController.h"
#include "Enemies/Public/ZR_ZombieAttackComponent.h"
#include "Enemies/Public/ZR_ZombieAttackAnimNotify.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AZR_ZombieCharacter::AZR_ZombieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = nullptr;
	AttackComponent = CreateDefaultSubobject<UZR_ZombieAttackComponent>("Attack Component");
	HealthComponent = CreateDefaultSubobject<UZR_HealthComponent>("Health Component");
}

// Called when the game starts or when spawned
void AZR_ZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAnimations();
	HealthComponent->OnDeath.AddUObject(this, &AZR_ZombieCharacter::OnDeathHandle);
	//AttackComponent->StartAttack();
}


void AZR_ZombieCharacter::InitAnimations()
{
	if (!DefaultAttackAnimMontage) return;
	UE_LOG(LogTemp, Warning, TEXT("YEAH!"))
	const auto Notifies = DefaultAttackAnimMontage->Notifies;

	for (auto NotifyEvent : Notifies)
	{
		UZR_ZombieAttackAnimNotify* event = Cast<UZR_ZombieAttackAnimNotify>(NotifyEvent.Notify);
		if (event)
		{
			event->onNotified.AddUObject(this, &AZR_ZombieCharacter::OnAttack);
			UE_LOG(LogTemp, Warning, TEXT("Found default animNotifies"))
			break;
		}
	}

	if (!PowerAttackAnimMontage) return;
	const auto HugeNotifies = PowerAttackAnimMontage->Notifies;

	for (auto NotifyEvent : HugeNotifies)
	{
		UZR_ZombieAttackAnimNotify* event = Cast<UZR_ZombieAttackAnimNotify>(NotifyEvent.Notify);
		if (event)
		{
			event->onNotified.AddUObject(this, &AZR_ZombieCharacter::OnHugeAttack);
			UE_LOG(LogTemp, Warning, TEXT("Found huge animNotifies"))
			break;
		}
	}
}

FVector AZR_ZombieCharacter::GetHandLocation()
{
	return GetMesh()->GetSocketLocation(MainHandSocketName);
}

void AZR_ZombieCharacter::OnAttack(USkeletalMeshComponent* MeshComp)
{
	if (MeshComp == GetMesh())
		AttackComponent->OnAttackDealt();
}

void AZR_ZombieCharacter::OnHugeAttack(USkeletalMeshComponent* MeshComp)
{
	if (MeshComp == GetMesh())
		AttackComponent->OnPowerAttackDealt();
}

// Called every frame
void AZR_ZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Error, TEXT("%s Health: %0.f"), *GetName(), HealthComponent->GetHealth());
}

// Called to bind functionality to input
void AZR_ZombieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AZR_ZombieCharacter::OnDeathHandle()
{
	//if (IsPendingKillPending()) return;
	GetCharacterMovement()->DisableMovement();
	if (GetController()) GetController()->UnPossess();
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->GetAnimInstance()->StopAllMontages(false);
	SetLifeSpan(5.f);

	GetMesh()->SetSimulatePhysics(true);
}