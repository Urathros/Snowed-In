// Fill out your copyright notice in the Description page of Project Settings.


#include "IceCrystal.h"

// Sets default values
AIceCrystal::AIceCrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the crystals hitbox and mesh
	SMCrystal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMCrystal"));
	CrystalHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));

	// Set the Static Mesh for the crystal
	SMCrystal->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(*SM_CRYSTAL_PATH).Object);

	// Attach the components
	RootComponent = SMCrystal;
	CrystalHitbox->SetupAttachment(RootComponent);

	// Gravity
	SMCrystal->SetSimulatePhysics(true);
	SMCrystal->SetEnableGravity(true);

	// Collision
	CrystalHitbox->SetSphereRadius(CRYSTAL_HITBOX_SIZE);
	CrystalHitbox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

#if WITH_EDITOR
	// Make the hitbox visible in the editor
	CrystalHitbox->bHiddenInGame = false;
#endif

}

void AIceCrystal::InitializeCrystal(int a_CrystalValue, FVector a_SpawnPoint, float a_CrystalLifetime)
{
	// Set properties of the crystal
	Value = a_CrystalValue;
	SpawnPoint = a_SpawnPoint;
	CrystalLifetime = a_CrystalLifetime;

	// Set the spawn point
	SetActorLocation(SpawnPoint);

	// Set Lifetime -> make sure the crystals are destroyed after a certain amount of time
	SetLifeSpan(CrystalLifetime);
}

// Called when the game starts or when spawned
void AIceCrystal::BeginPlay()
{
	Super::BeginPlay();

//! Needs to be removed after SpawnManager is implemented
#if WITH_EDITOR
	InitializeCrystal(167, FVector(1400, 1820.0, 5000), CrystalLifetime);
#endif
}

// Called every frame
void AIceCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

