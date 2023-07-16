// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/ZR_ReloadNotify.h"

void UZR_ReloadNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	onNotified.Broadcast();

	Super::Notify(MeshComp, Animation, EventReference);
}