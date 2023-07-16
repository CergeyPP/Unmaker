// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AIController.h"

#include "ZombieRangeGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNewWaveDelegate);

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data")
	int32 MinZombieCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data")
	int32 ZombiePerWaveAddition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data")
	float TimeBeforeNewWave;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data")
		float ZombieSpawnRate;
};

UENUM()
enum class EGameState : uint8
{
	InProgress = 1,
	Pause,
	GameOver,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EGameState)

UCLASS()
class ZOMBIERANGE_API AZombieRangeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AZombieRangeGameModeBase();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data")
	FGameData GameData;

	virtual void StartPlay() override;
	void StartWave();

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController*) override;
	virtual bool SetPause(APlayerController* Player, FCanUnpause CanUnpause = FCanUnpause()) override;

	virtual bool ClearPause() override;

	int32 GetWaveCounter() const;

	UPROPERTY(BlueprintAssignable)
	FOnNewWaveDelegate OnNewWave;

	FOnGameStateChangedSignature OnGameStateChanged;

	bool IsNewWaveComing() { return isNewWaveComing; }

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerScore() const { return PlayerScore; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data")
		TSubclassOf<APawn> ZombiePawnClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data")
		TSubclassOf<AAIController> ZombieControllerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data")
		FString ZombieStartTag;

	virtual void RestartPlayer(AController* Player) override;

	void OnCharacterDiedHandle();

private:

	EGameState GameState;

	FTimerHandle WaveSpawnTimerHandle;
	FTimerHandle ZombieSpawnTimer;

	TArray<AAIController*> Controllers;

	AAIController* CreateAIController();

	UFUNCTION()
	void OnControllerPossessNewPawn(APawn* oldPawn, APawn* NewPawn);

	int32 LastSpawnControllerIndex;
	void SetupAIController(AAIController* Controller);
	void SpawnNewZombie();
	int32 WaveCount;
	int32 ZombieCount;

	bool isNewWaveComing;

	void OnZombieDiedHandle();

	void SetGameState(EGameState State);

	int32 PlayerScore;
};
