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

	// Get the GameManager
	if (GM = UGameManager::Instantiate(*this); !GM) UE_LOG(LogTemp, Error, TEXT("IceCrystalManager: No GameManager was found!"));
	GM->HandleWaveChangedDelegate.BindUObject(this, &ACrystalSpawnManager::StartSpawnTimer);
	UE_LOG(LogTemp, Warning, TEXT("IceCrystal: StartSpawnTimerBind"));
	GM->HandleWaveClearedDelegate.BindUObject(this, &ACrystalSpawnManager::StopSpawnTimer);
	UE_LOG(LogTemp, Warning, TEXT("IceCrystal: StopSpawnTimerBind"));
	
	// !NOTE: Debugging purposes -> Needs to be removed
	if (bDebug) StartSpawnTimer();
}

// Called every frame
void ACrystalSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACrystalSpawnManager::StartSpawnTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("IceCrystal: StartSpawnTimer"));
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ACrystalSpawnManager::SpawnCrystal, SpawnRate, true);
}

void ACrystalSpawnManager::StopSpawnTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("IceCrystal: StopSpawnTimer"));
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
}

void ACrystalSpawnManager::SpawnCrystal()
{
	if (GM && GM->GetWaveSpawnInProgress() == false)
	{
		if (bDebug) CrystalValue = FMath::RoundToInt((DebugWave * CrystalBaseValue) * CrystalMultiplierPerWave);
		else CrystalValue = FMath::RoundToInt((GM->GetWave() * CrystalBaseValue) * CrystalMultiplierPerWave);

		UE_LOG(LogTemp, Warning, TEXT("IceCrystal: GM-Wave: %d"), GM->GetWave());
		UE_LOG(LogTemp, Warning, TEXT("IceCrystal: Debug-Wave: %d"), DebugWave);
		UE_LOG(LogTemp, Warning, TEXT("IceCrystal: CrystalBaseValue: %d"), CrystalBaseValue);
		UE_LOG(LogTemp, Warning, TEXT("IceCrystal: CrystalMultiplierPerWave: %f"), CrystalMultiplierPerWave);
		UE_LOG(LogTemp, Warning, TEXT("IceCrystal: CrystalValue: %d"), CrystalValue);

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
}

void ACrystalSpawnManager::RemoveCrystal(AActor* a_Crystal)
{
	SpawnPool.Remove(Cast<AIceCrystal>(a_Crystal));

	// UE_LOG the destroyed crystal name
	UE_LOG(LogTemp, Warning, TEXT("IceCrystal: Destroyed: %s"), *a_Crystal->GetName());
}