// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ZR_NewWaveWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIERANGE_API UZR_NewWaveWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
		bool IsNewWaveOccuried() const;

	//virtual bool Initialize() override;

private:

	FTimerHandle AnnounceFadeTimer;
	bool bIsNewWave;

	void OnNewWaveHandle();
	void TurnWidgetOff();
};
