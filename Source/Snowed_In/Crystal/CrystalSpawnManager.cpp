// Fill out your copyright notice in the Description page of Project Settings.


#include "CrystalSpawnManager.h"
#include "TimerManager.h"

// Sets default values
ACrystalSpawnManager::ACrystalSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void ACrystalSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ACrystalSpawnManager::SpawnCrystal, SpawnRate, true);
}

// Called every frame
void ACrystalSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACrystalSpawnManager::SpawnCrystal()
{
	if (SpawnPool.Num() < MaxCrystals && SpawnPoints.Num() > 0)
	{
		int32 SpawnIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		FVector SpawnLocation = SpawnPoints[SpawnIndex];

		NewCrystal = GetWorld()->SpawnActor<AIceCrystal>(AIceCrystal::StaticClass(), SpawnLocation, FRotator::ZeroRotator);
		if (NewCrystal)
		{
			NewCrystal->InitializeCrystal(CrystalValue, CrystalLifetime, ReductionDelay);
			SpawnPool.Add(NewCrystal);
			
			// Remove Crystal from the pool when its lifetime has expired
			NewCrystal->OnDestroyed.AddDynamic(this, &ACrystalSpawnManager::RemoveCrystal);
		}
	}
}

void ACrystalSpawnManager::RemoveCrystal(AActor* a_Crystal)
{
	SpawnPool.Remove(Cast<AIceCrystal>(a_Crystal));

	// UE_LOG the destroyed crystal name
	UE_LOG(LogTemp, Warning, TEXT("IceCrystal: Destroyed: %s"), *a_Crystal->GetName());
}