// Copyright Epic Games, Inc. All Rights Reserved.


#include "ZombieRangeGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "ZR_MainCharacter.h"
#include "Health/ZR_HealthComponent.h"
#include "Public/ZR_PlayerController.h"

AZombieRangeGameModeBase::AZombieRangeGameModeBase()
{
	DefaultPawnClass = AZR_MainCharacter::StaticClass();
	
}

void AZombieRangeGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (!GetWorld()) return;

	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	const auto Pawn = PlayerController->GetPawn();
	if (!Pawn) return;

	const auto HealthComponent = Cast<UZR_HealthComponent>(Pawn->GetComponentByClass(UZR_HealthComponent::StaticClass()));
	if (!HealthComponent) return;

	HealthComponent->OnDeath.AddUObject(this, &AZombieRangeGameModeBase::OnCharacterDiedHandle);

	for (int32 i = 0; i < GameData.MinZombieCount; i++)
	{
		const auto Controller = CreateAIController();
		if (Controller)
		{
			Controllers.Add(Controller);
			Controller->OnPossessedPawnChanged.AddDynamic(this, &AZombieRangeGameModeBase::OnControllerPossessNewPawn);
		}
	}
	PlayerScore = 0;
	isNewWaveComing = true;
	WaveCount = 0;
	ZombieCount = 0;
	StartWave();

	SetGameState(EGameState::InProgress);
}

void AZombieRangeGameModeBase::StartWave()
{
	if (!GetWorld()) return;


	for (int32 i = 0; i < GameData.ZombiePerWaveAddition; i++)
	{
		const auto Controller = CreateAIController();
		if (Controller)
		{
			Controllers.Add(Controller);
			Controller->OnPossessedPawnChanged.AddDynamic(this, &AZombieRangeGameModeBase::OnControllerPossessNewPawn);
		}
	}

	LastSpawnControllerIndex = 0;
	GetWorldTimerManager().SetTimer(ZombieSpawnTimer, this, &AZombieRangeGameModeBase::SpawnNewZombie, GameData.ZombieSpawnRate, true);

	++WaveCount;
	GetWorld()->GetTimerManager().ClearTimer(WaveSpawnTimerHandle);
	isNewWaveComing = false;
	//ZombieCount = Controllers.Num();
}

UClass* AZombieRangeGameModeBase::GetDefaultPawnClassForController_Implementation(AController*  Controller)
{
	if (Controller && Controller->IsA<AAIController>())
		return ZombiePawnClass;
	else
		return Super::GetDefaultPawnClassForController_Implementation(Controller);
}

int32 AZombieRangeGameModeBase::GetWaveCounter() const
{
	return WaveCount;
}

bool AZombieRangeGameModeBase::SetPause(APlayerController* Player, FCanUnpause CanUnpause)
{
	bool Pause = Super::SetPause(Player, CanUnpause);
	if (Pause)
		SetGameState(EGameState::Pause);

	return Pause;
}

bool AZombieRangeGameModeBase::ClearPause()
{
	bool Pause = Super::ClearPause();

	if (Pause)
	{
		SetGameState(EGameState::InProgress);
	}

	return Pause;
}

void AZombieRangeGameModeBase::RestartPlayer(AController* Player)
{
	if (Player && Player->IsA<AAIController>())
	{
		if (Player->IsPendingKillPending()) return;

		TArray<APlayerStart*> PlayerStarts;

		for (TActorIterator<APlayerStart> it(GetWorld()); it; ++it)
		{
			if ((*it)->PlayerStartTag.ToString() == ZombieStartTag)
				PlayerStarts.Add(*it);
		}
		
		AActor* StartSpot;
		if (PlayerStarts.Num() == 0)
			StartSpot = nullptr;
		else
			StartSpot = PlayerStarts[FMath::RandRange(0, PlayerStarts.Num() - 1)];

		// If a start spot wasn't found,
		if (StartSpot == nullptr)
		{
			// Check for a previously assigned spot
			if (Player->StartSpot != nullptr)
			{
				StartSpot = Player->StartSpot.Get();
				UE_LOG(LogGameMode, Warning, TEXT("RestartPlayer: Zombie Player start not found, using last start spot"));
			}
		}

		RestartPlayerAtPlayerStart(Player, StartSpot);
	}
	else if (Player && Player->IsA<APlayerController>())
	{
		if(Player->IsPendingKillPending()) return;

		AActor* StartSpot = FindPlayerStart(Player, "Player");

		// If a start spot wasn't found,
		if (StartSpot == nullptr)
		{
			// Check for a previously assigned spot
			if (Player->StartSpot != nullptr)
			{
				StartSpot = Player->StartSpot.Get();
				UE_LOG(LogGameMode, Warning, TEXT("RestartPlayer: Player start not found, using last start spot"));
			}
		}

		RestartPlayerAtPlayerStart(Player, StartSpot);
	}
	else
	{
		Super::RestartPlayer(Player);
	}
	
	return;
}

void AZombieRangeGameModeBase::OnCharacterDiedHandle()
{
	SetGameState(EGameState::GameOver);
	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}
}

AAIController* AZombieRangeGameModeBase::CreateAIController()
{
	FActorSpawnParameters SpawnParametrs;
	SpawnParametrs.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	return GetWorld()->SpawnActor<AAIController>(ZombieControllerClass, SpawnParametrs);
}

void AZombieRangeGameModeBase::OnControllerPossessNewPawn(APawn* OldPawn, APawn* NewPawn)
{
	if (OldPawn && !NewPawn)
		OnZombieDiedHandle();
}

void AZombieRangeGameModeBase::SetupAIController(AAIController* Controller)
{
	RestartPlayer(Controller);
	const auto Pawn = Controller->GetPawn();

	if (!Pawn || !IsValid(Pawn) || Controller->GetStateName() == NAME_Inactive) return;
	/*const auto HealthComponent = Cast<UZR_HealthComponent>(Pawn->GetComponentByClass(UZR_HealthComponent::StaticClass()));
	if (!HealthComponent) return;*/

	ZombieCount++;
}

void AZombieRangeGameModeBase::SpawnNewZombie()
{
	while (LastSpawnControllerIndex < Controllers.Num())
	{
		const auto Controller = Controllers[LastSpawnControllerIndex];
		LastSpawnControllerIndex++;
		if (!Controller->GetPawn())
		{
			SetupAIController(Controller);
			return;
		}
		//HealthComponent->OnDeath.AddUObject(this, &AZombieRangeGameModeBase::OnZombieDiedHandle);
	}

	GetWorld()->GetTimerManager().ClearTimer(ZombieSpawnTimer);
}

void AZombieRangeGameModeBase::OnZombieDiedHandle()
{
	ZombieCount--;
	PlayerScore += 100;
	if (ZombieCount == 0)
	{
		isNewWaveComing = true;
		GetWorld()->GetTimerManager().SetTimer(WaveSpawnTimerHandle, this, &AZombieRangeGameModeBase::StartWave, GameData.TimeBeforeNewWave, false);
	}
}

void AZombieRangeGameModeBase::SetGameState(EGameState State)
{
	if (GameState == State) return;

	GameState = State;
	OnGameStateChanged.Broadcast(State);
}
