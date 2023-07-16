// Fill out your copyright notice in the Description page of Project Settings.


#include "ZR_MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AZR_MainCharacter::AZR_MainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());

	WeaponSocket = CreateDefaultSubobject<USceneComponent>("WeaponSocket");
	WeaponSocket->SetupAttachment(CameraComponent);

	WeaponComponent = CreateDefaultSubobject<UZR_WeaponComponent>("WeaponComponent");
	WeaponComponent->SetWeaponSocket(WeaponSocket);

	HealthComponent = CreateDefaultSubobject<UZR_HealthComponent>("Health Component");
	//GetMesh()->SetupAttachment(CameraComponent);
}

// Called when the game starts or when spawned
void AZR_MainCharacter::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnDeath.AddUObject(this, &AZR_MainCharacter::OnDeathHandle);
}

// Called every frame
void AZR_MainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%0.f"), HealthComponent->GetHealth());
}

// Called to bind functionality to input
void AZR_MainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AZR_MainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AZR_MainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AZR_MainCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &AZR_MainCharacter::TurnAround);
	PlayerInputComponent->BindAction("Pistol", IE_Pressed, this, &AZR_MainCharacter::OnEquipPistol);
	PlayerInputComponent->BindAction("Shotgun", IE_Pressed, this, &AZR_MainCharacter::OnEquipShotgun);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AZR_MainCharacter::Jump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UZR_WeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UZR_WeaponComponent::StopFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UZR_WeaponComponent::Reload);
	
}

void AZR_MainCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AZR_MainCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void AZR_MainCharacter::TurnAround(float Amount)
{
	AddControllerYawInput(Amount);
}

void AZR_MainCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void AZR_MainCharacter::OnDeathHandle()
{
	GetCharacterMovement()->DisableMovement();
	const auto PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->ChangeState(NAME_Spectating);
	}
	SetLifeSpan(1.f);
}

void AZR_MainCharacter::OnEquipPistol()
{
	WeaponComponent->Equip(0);
}

void AZR_MainCharacter::OnEquipShotgun()
{
	WeaponComponent->Equip(1);
}