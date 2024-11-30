// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager.generated.h"

DECLARE_DELEGATE(FHandleIceCrystalsChangedSignature);
DECLARE_DELEGATE(FHandleWaveClearedSignature);
DECLARE_DELEGATE(FHandleWaveChangedSignature);
DECLARE_DELEGATE(FHandleInBuildChangedSignature);
DECLARE_DELEGATE(FHandleHUDCreationSignature);

class AEnemySpawner;

/**
 * 
 */
UCLASS(BlueprintType)
class SNOWED_IN_API UGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	static auto GetGameInstance(const UObject& a_target) -> UGameInstance* const;
public:

	// Get the Game Manager with this
	static auto Instantiate(const UObject& a_target) -> UGameManager* const;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize();

	static auto ConvertPosToGrid(const FVector& a_pos) -> const FVector;

	/*************************************************************************/
	#pragma region Getter/Setter
	/*************************************************************************/

	// Check if the Game is Paused
	auto GetPause(void) const -> const bool;

	// (Un)set the Game paused.
	auto SetPause(const bool& a_bPause) -> UGameManager&;


	// Get the current Number of Ice crystals
	auto GetIceCrystals(void) const -> const uint32;

	// Set the current Number of Ice crystalls
	auto SetIceCrystals(const uint32& a_IceCrystals) -> UGameManager&;

	// Add a number of ice crystals to the counter
	auto AddIceCrystals(const uint32& a_IceCrystals) -> UGameManager&;

	// Substract a number of ice crystals to the counter
	auto SubstractIceCrystals(const uint32& a_IceCrystals) -> UGameManager&;

	// Increment the ice crystal counter
	auto IncrementIceCrystals(void) -> UGameManager&;

	// Decrement the ice crystal counter
	auto DecrementIceCrystals(void) -> UGameManager&;

	auto GetWave(void) const -> const uint32;
	auto SetWave(const uint32& a_Wave) -> UGameManager&;
	auto IncrementWave(void) -> UGameManager&;
	auto SetWaveSpawnInProgress(const bool& a_bInProgress) -> UGameManager&;
	auto GetWaveSpawnInProgress(void) const -> const bool;

	auto IncrementEnemyCount(void) -> UGameManager&;
	auto DecrementEnemyCount(void) -> UGameManager&;
	auto GetEnemyCount(void) const -> const int32;

	auto GetEnemySpawner(void) -> AEnemySpawner*;
	auto SetEnemySpawner(AEnemySpawner* a_spawner) -> UGameManager&;

	auto SetInBuildMode(const bool& a_bInBuildMode) -> UGameManager&;
	auto GetInBuildMode(void) const -> const bool;

	auto InvokeHUDBuilding(void) -> UGameManager&;
#pragma endregion
	/*************************************************************************/
private:
	/*************************************************************************/
	#pragma region MemberVariables
	/*************************************************************************/

	// Controlls if the game is paused.
	bool bPause = false;

	// Counter of global ice crystals
	uint32 IceCrystals = 0;

	// Counter of current wave
	uint32 CurrentWave = 0;

	// Whether a wave is currently in the spawning phase
	bool bWaveSpawnInProgress = false;

	// How many enemies are currently in the Level
	int32 EnemyCount = 0;

	// Reference to the Enemy Spawner
	class AEnemySpawner* EnemySpawner = nullptr;

	bool bInBuildMode = true;

	#pragma endregion
	/*************************************************************************/

	static const int32 GridSize = 200; // 2x2 Meters per Grid Cell

public:
	FHandleIceCrystalsChangedSignature HandleIceCrystalsChangedDelegate = nullptr;
	FHandleWaveClearedSignature HandleWaveClearedDelegate = nullptr;
	FHandleWaveChangedSignature HandleWaveChangedDelegate = nullptr;
	FHandleInBuildChangedSignature HandleInBuildChangedDelegate = nullptr;
	FHandleHUDCreationSignature HandleHUDCreationDelegate = nullptr;
};