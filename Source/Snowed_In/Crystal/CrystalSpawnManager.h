// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IceCrystal.h"
#include "../Core/GameManager.h"
#include "CrystalSpawnManager.generated.h"

UCLASS()
class SNOWED_IN_API ACrystalSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrystalSpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Functions
	void SpawnCrystal();

	UFUNCTION()
	void StartSpawnTimer();

	UFUNCTION()
	void StopSpawnTimer();

	UFUNCTION()
	void RemoveCrystal(AActor* a_Crystal);

#pragma region UPROPERTY

	// Components
	UGameManager* GM = nullptr;

	FTimerHandle SpawnTimerHandle;
	AIceCrystal* NewCrystal = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	TArray<AIceCrystal*> SpawnPool;

	// Properties
	UPROPERTY(EditAnywhere, Category = "Spawn Properties")
	TArray<FVector> SpawnPoints;

	UPROPERTY(EditAnywhere, Category = "Spawn Properties")
	int MaxCrystals = 10;

	UPROPERTY(EditAnywhere, Category = "Spawn Properties")
	float SpawnRate = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Crystal Properties")
	int CrystalBaseValue = 10;
	
	UPROPERTY(EditAnywhere, Category = "Crystal Properties")
	int CrystalValue = 0;

	UPROPERTY(EditAnywhere, Category = "Crystal Properties")
	float CrystalMultiplierPerWave = 1.5f;

	UPROPERTY(EditAnywhere, Category = "Crystal Properties")
	float CrystalLifetime = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Crystal Properties")
	float ReductionDelay = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDebug = false;

	UPROPERTY(EditAnywhere, Category = "Debug")
	int DebugWave = 1;

#pragma endregion
};
