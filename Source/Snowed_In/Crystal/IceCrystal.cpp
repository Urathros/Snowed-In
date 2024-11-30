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
	CrystalHitbox->SetCollisionProfileName(TEXT("OverlapAll"));

	// Enable HitEvents
	CrystalHitbox->SetGenerateOverlapEvents(true);

	// Bind the hit event
	CrystalHitbox->OnComponentBeginOverlap.AddDynamic(this, &AIceCrystal::EventHit);

#if WITH_EDITOR
	// Make the hitbox visible in the editor
	CrystalHitbox->bHiddenInGame = false;
#endif

}

void AIceCrystal::InitializeCrystal(int a_CrystalValue, float a_CrystalLifetime, float a_ReductionDelay)
{
	// Set properties of the crystal
	Value = a_CrystalValue;
	Lifetime = a_CrystalLifetime;
	ReductionDelay = a_ReductionDelay;

	// Set Lifetime of the crystal
	SetLifeSpan(Lifetime);
}

// Called when the game starts or when spawned
void AIceCrystal::BeginPlay()
{
	Super::BeginPlay();

	// Get the GameManager
	
	if(GM = UGameManager::Instantiate(*this); !GM) UE_LOG(LogTemp, Error, TEXT("IceCrystal: No GameManager was found!"));
}

// Called every frame
void AIceCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if the crystal's lifespan has expired and destroy it
	if (GetLifeSpan() <= 0)
	{
		Destroy();
	}
}

void AIceCrystal::EventHit(UPrimitiveComponent* a_pOverlappedComponent, AActor* a_pOtherActor,
	UPrimitiveComponent* a_pOtherComp, int32 a_OtherBodyIndex, bool bFromSweep,
	const FHitResult& a_SweepResult)
{
	// UE Log all arguments
	// UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *a_pOverlappedComponent->GetName());
	// UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *a_pOtherActor->GetName());
	// UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *a_pOtherComp->GetName());

	// if the other actor is a player Snowed_InCharacter
	if (a_pOtherActor->IsA(ASnowed_InCharacter::StaticClass()))
	{
		if (GM)
		{
			GM->AddIceCrystals(Value);
			UE_LOG(LogTemp, Warning, TEXT("IceCrystal: PickedUp %d"), Value);
			Destroy();
			int currentIC = GM->GetIceCrystals();
			UE_LOG(LogTemp, Warning, TEXT("IceCrystal: Current Ice Crystals %d"), currentIC);
		}
		else UE_LOG(LogTemp, Error, TEXT("IceCrystal: No GameManager was found!"));
	}
	if (!a_pOtherActor->IsA(AIceCrystal::StaticClass()))
	{
			//UE_LOG(LogTemp, Warning, TEXT("IceCrystal: Overlapped Component %s"), *a_pOverlappedComponent->GetName());
			GetWorldTimerManager().SetTimer(ValueTimerHandle, this, &AIceCrystal::ReduceValue, 1.0f, true, ReductionDelay);
	}
}

void AIceCrystal::ReduceValue()
{
	if (Value <= 0) Destroy();
	else Value--;

	UE_LOG(LogTemp, Warning, TEXT("IceCrystal: Value %d"), Value);
}
