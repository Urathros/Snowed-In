// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/GameManager.h"
#include "Enemy/EnemySpawner.h"
#include <Kismet/GameplayStatics.h>
#include "../Environment/CalendarSystem.h"
#include "GameManager.h"

auto UGameManager::GetGameInstance(const UObject& a_target) -> UGameInstance* const
{
	if (a_target.GetWorld() && a_target.GetWorld()->GetGameInstance())
	{
		return UGameplayStatics::GetGameInstance(a_target.GetWorld());
	}
	else if (a_target.IsA(AActor::StaticClass()))
	{
		if (Cast<AActor>(&a_target)->GetGameInstance()) return GEngine->GetWorld()->GetGameInstance();
	}
	return nullptr;
}

auto UGameManager::Instantiate(const UObject& a_target) -> UGameManager* const
{
	auto instance = GetGameInstance(a_target);
	if (instance) return instance->GetSubsystem<UGameManager>();

	return nullptr;
}

void UGameManager::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Display, TEXT("Game Manager initialized."));
}

void UGameManager::Deinitialize()
{
	UE_LOG(LogTemp, Display, TEXT("Game Manager finalized."));
}

auto UGameManager::ConvertPosToGrid(const FVector& a_pos) -> const FVector
{
	auto convertedPos = FVector::Zero();
	convertedPos.X = a_pos.X - ((int32)a_pos.X % GridSize);
	convertedPos.Y = a_pos.Y - ((int32)a_pos.Y % GridSize);

	//convertedPos += FVector(GridSize, GridSize, 0.f) * 0.5f;

	return convertedPos;
}

auto UGameManager::GetPause() const -> const bool
{
	return bPause;
}

auto UGameManager::SetPause(const bool& a_bPause) -> UGameManager&
{
	bPause = a_bPause;
	return *this;
}

auto UGameManager::GetIceCrystals(void) const -> const uint32
{
	return IceCrystals;
}

auto UGameManager::SetIceCrystals(const uint32& a_IceCrystals) -> UGameManager&
{
	IceCrystals = a_IceCrystals;
	HandleIceCrystalsChangedDelegate.ExecuteIfBound();
	return *this;
}

auto UGameManager::AddIceCrystals(const uint32& a_IceCrystals) -> UGameManager&
{
	IceCrystals += a_IceCrystals;
	HandleIceCrystalsChangedDelegate.ExecuteIfBound();
	return *this;
}

auto UGameManager::SubstractIceCrystals(const uint32& a_IceCrystals) -> UGameManager&
{
	IceCrystals -= a_IceCrystals;
	HandleIceCrystalsChangedDelegate.ExecuteIfBound();
	return *this;
}

auto UGameManager::IncrementIceCrystals(void) -> UGameManager&
{
	IceCrystals++;
	HandleIceCrystalsChangedDelegate.ExecuteIfBound();
	return *this;
}

auto UGameManager::DecrementIceCrystals(void) -> UGameManager&
{
	IceCrystals--;
	HandleIceCrystalsChangedDelegate.ExecuteIfBound();
	return *this;
}

auto UGameManager::GetWave(void) const -> const uint32
{
    return CurrentWave;
}

auto UGameManager::SetWave(const uint32& a_Wave) -> UGameManager&
{
    CurrentWave = a_Wave;
	HandleWaveChangedDelegate.ExecuteIfBound();
	return *this;
}

auto UGameManager::IncrementWave(void) -> UGameManager&
{
	CurrentWave++;
	HandleWaveChangedDelegate.ExecuteIfBound();
	return *this;
}

auto UGameManager::SetWaveSpawnInProgress(const bool& a_bInProgress)->UGameManager&
{
	bWaveSpawnInProgress = a_bInProgress;
	return *this;
}

auto UGameManager::GetWaveSpawnInProgress(void) const -> const bool
{
	return bWaveSpawnInProgress;
}

auto UGameManager::IncrementEnemyCount(void) -> UGameManager&
{
	EnemyCount++;
	return *this;
}

auto UGameManager::DecrementEnemyCount(void) -> UGameManager&
{
	EnemyCount--;

	if (EnemyCount == 0 && bWaveSpawnInProgress == false)
	{
		HandleWaveClearedDelegate.ExecuteIfBound();
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Wave Defeated !!");
		SetInBuildMode(true);
	}

	return *this;
}

auto UGameManager::GetEnemyCount(void) const -> const int32
{
	return EnemyCount;
}

auto UGameManager::GetEnemySpawner(void) -> AEnemySpawner*
{
	return EnemySpawner;
}

auto UGameManager::SetEnemySpawner(AEnemySpawner* a_spawner) -> UGameManager&
{
	EnemySpawner = a_spawner;
	return *this;
}

/// <summary>
/// Use this function to Set the bInBuildMode variable and automatically start the next wave, when exiting build mode
/// </summary>
/// <param name="a_bInBuildMode">Whether to be in build mode or not</param>
/// <returns>A ref to the GameManager for Functional programming</returns>
auto UGameManager::SetInBuildMode(const bool& a_bInBuildMode) -> UGameManager&
{
	// Updating Variable
	bInBuildMode = a_bInBuildMode;
	HandleInBuildChangedDelegate.ExecuteIfBound();

	// Starting next Wave if exiting Build Mode
	if (bInBuildMode == false && EnemySpawner) EnemySpawner->StartNextWave();

	if(CalendarSystem) CalendarSystem->ForwardTime();

	return *this;
}

auto UGameManager::GetInBuildMode(void) const -> const bool
{
	return bInBuildMode;
}

auto UGameManager::InvokeHUDBuilding(void) -> UGameManager&
{
	HandleHUDCreationDelegate.ExecuteIfBound();
	return *this;
}

auto UGameManager::GetCalendarSystem(void) -> ACalendarSystem*
{
	return CalendarSystem;
}

auto UGameManager::SetCalendarSystem(ACalendarSystem* a_Calendar) -> UGameManager&
{
	CalendarSystem = a_Calendar;
	return *this;
}

auto UGameManager::InvokeGameOver(void) -> UGameManager&
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "GAME OVER");
	HandleGameOverDelegate.ExecuteIfBound();
	return *this;
}