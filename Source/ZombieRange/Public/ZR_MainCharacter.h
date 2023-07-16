// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "ZR_WeaponComponent.h"
#include "Health/ZR_HealthComponent.h"

#include "ZR_MainCharacter.generated.h"


UCLASS()
class ZOMBIERANGE_API AZR_MainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AZR_MainCharacter();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* WeaponSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UZR_WeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		UZR_HealthComponent* HealthComponent;

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void TurnAround(float Amount);
	void LookUp(float Amount);

	void OnDeathHandle();
	void OnEquipPistol();
	void OnEquipShotgun();
};
