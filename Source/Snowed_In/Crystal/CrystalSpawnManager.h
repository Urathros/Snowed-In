// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IceCrystal.h"
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
	void RemoveCrystal(AActor* a_Crystal);

#pragma region UPROPERTY

	// Components
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
	int CrystalValue = 10;

	UPROPERTY(EditAnywhere, Category = "Crystal Properties")
	float CrystalLifetime = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Crystal Properties")
	float ReductionDelay = 1.0f;

#pragma endregion
};