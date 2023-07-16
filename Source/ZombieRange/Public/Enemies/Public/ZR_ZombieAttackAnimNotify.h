// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ZR_ZombieAttackAnimNotify.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamageDealNotified, USkeletalMeshComponent*)

UCLASS()
class ZOMBIERANGE_API UZR_ZombieAttackAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:

	FOnDamageDealNotified onNotified;
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
