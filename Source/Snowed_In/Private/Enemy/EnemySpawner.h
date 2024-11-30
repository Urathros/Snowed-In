// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "EnemySpawner.generated.h"

USTRUCT(BlueprintType)
struct FWaveData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LvlOneCount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LvlTwoCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LvlThreeCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UsedStartPointCount = 1;
};



UCLASS()
class AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartNextWave(void);

private:
	void SpawnEnemy(void);
	FWaveData* GetWaveDataRow(int32 a_idx);

	UPROPERTY(EditAnywhere, Category = "Wave Settings")
	UDataTable* WaveData = nullptr;

	UPROPERTY(EditAnywhere, Category = "Wave Settings")
	TArray<TSubclassOf<class AEnemy>> Enemies = {};

	UPROPERTY(EditAnywhere, Category = "Wave Settings")
	TArray<AActor*> SpawnPoints = {};

	UPROPERTY(EditAnywhere, Category = "Wave Settings")
	float TimeBetweenEnemies = 0.5f;

	FTimerHandle SpawnTimerHandle = {};

	int32 CurrentWave = 0;
	int32 MaxWaveCount = 0;

	FWaveData ToSpawn = {};

	class UGameManager* GM = nullptr;
};