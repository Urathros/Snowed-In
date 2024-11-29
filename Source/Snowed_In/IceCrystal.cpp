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


}

void AIceCrystal::InitializeCrystal(int a_CrystalValue)
{
	Value = a_CrystalValue;
}

// Called when the game starts or when spawned
void AIceCrystal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIceCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

