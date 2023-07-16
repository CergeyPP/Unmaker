// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ZR_ReloadNotify.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnReloadNotified)

UCLASS()
class ZOMBIERANGE_API UZR_ReloadNotify : public UAnimNotify
{
	GENERATED_BODY()
public:

	FOnReloadNotified onNotified;
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
