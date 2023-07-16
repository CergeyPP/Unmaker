// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Public/ZR_ZombieAttackAnimNotify.h"

void UZR_ZombieAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	onNotified.Broadcast(MeshComp);

	Super::Notify(MeshComp, Animation, EventReference);
}