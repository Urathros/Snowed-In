// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/Enemy.h"
#include "Enemy/EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	if (WaveData) MaxWaveCount = WaveData->GetRowMap().Num();
	if (Enemies.Num() != 3) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Enemies need to be three");

	StartNextWave();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::StartNextWave(void)
{
	CurrentWave++;
	if (CurrentWave > MaxWaveCount)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "You have defeated ALL waves");
		return;
	}

	ToSpawn = *GetWaveDataRow(CurrentWave - 1);

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, TimeBetweenEnemies, true, 0.0f);
}

void AEnemySpawner::SpawnEnemy(void)
{
	int rngRange = 0;
	if (ToSpawn.LvlOneCount > 0) rngRange++;
	if (ToSpawn.LvlTwoCount > 0) rngRange++;
	if (ToSpawn.LvlThreeCount > 0) rngRange++;

	if (rngRange == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, "Wave Done");
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	auto enemyIdx = FMath::RandRange(0, rngRange);
	if (enemyIdx == 1 && ToSpawn.LvlTwoCount <= 0) enemyIdx = 2;

	auto spawnPointIdx = FMath::RandRange(0, FMath::Clamp(ToSpawn.UsedStartPointCount - 1, 0, 5));
	auto spawnPoint = SpawnPoints[spawnPointIdx];

	auto enemy = GetWorld()->SpawnActor<AEnemy>(Enemies[enemyIdx], spawnPoint->GetActorLocation(), spawnPoint->GetActorRotation());

	switch (rngRange)
	{
	case 1:
		ToSpawn.LvlOneCount--;
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Magenta, FString::Printf(TEXT("1 rmv => %d"), ToSpawn.LvlOneCount));
		break;

	case 2:
		ToSpawn.LvlTwoCount--;
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Magenta, FString::Printf(TEXT("2 rmv => %d"), ToSpawn.LvlTwoCount));
		break;

	case 3:
		ToSpawn.LvlThreeCount--;
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Magenta, FString::Printf(TEXT("3 rmv => %d"), ToSpawn.LvlThreeCount));
		break;

	default:
		break;
	}
}

FWaveData* AEnemySpawner::GetWaveDataRow(int32 a_idx)
{
	if (!WaveData) return nullptr;

	auto rowNames = WaveData->GetRowNames();

	if (a_idx >= 0 && a_idx < rowNames.Num())
	{
		auto rowName = rowNames[a_idx];
		auto row = WaveData->FindRow<FWaveData>(rowName, "");

		if (row) return row;
	}

	return nullptr;
}
