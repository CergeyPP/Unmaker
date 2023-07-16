// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ZR_EquipNotify.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEquipNotified)

UCLASS()
class ZOMBIERANGE_API UZR_EquipNotify : public UAnimNotify
{
	GENERATED_BODY()
public:

	FOnEquipNotified onNotified;
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
