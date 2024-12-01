// Fill out your copyright notice in the Description page of Project Settings.


#include "../Buildings/Tower.h"
#include "Components/SphereComponent.h"
#include "Enemy/Enemy.h"
#include "Components/AudioComponent.h"
#include "../Bullets/Bullet.h"

// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto mesh1 = ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_LVL1_PATH);
	if (mesh1.Succeeded()) lvlOneMesh = mesh1.Object;
	auto mesh2 = ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_LVL2_PATH);
	if (mesh2.Succeeded()) lvlTwoMesh = mesh2.Object;
	auto mesh3 = ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_LVL3_PATH);
	if (mesh3.Succeeded()) lvlThreeMesh = mesh3.Object;

	auto mat = ConstructorHelpers::FObjectFinder<UMaterialInstance>(*MAT_PATH);

	auto towerLvl1Sounds = ConstructorHelpers::FObjectFinder<USoundBase>(*TOWER_LVL1_SFX_PATH);
	auto towerLvl2Sounds = ConstructorHelpers::FObjectFinder<USoundBase>(*TOWER_LVL2_SFX_PATH);
	if (towerLvl2Sounds.Succeeded()) lvlTwoSounds = towerLvl2Sounds.Object;
	auto towerLvl3Sounds = ConstructorHelpers::FObjectFinder<USoundBase>(*TOWER_LVL3_SFX_PATH);
	if (towerLvl3Sounds.Succeeded()) lvlThreeSounds = towerLvl3Sounds.Object;

	Visuals = CreateDefaultSubobject<UStaticMeshComponent>("Visuals");
	if (lvlOneMesh) Visuals->SetStaticMesh(lvlOneMesh);
	if (mat.Succeeded()) Visuals->SetMaterial(0, mat.Object);
	SetRootComponent(Visuals);

	PerceptionTrigger = CreateDefaultSubobject<USphereComponent>("Perception Trigger");
	PerceptionTrigger->SetSphereRadius(AttentionRadius);
	PerceptionTrigger->SetCollisionProfileName(*DEFAULT_COLLISION_PROFILE_NAME);
	PerceptionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnBeginOverlap);
	PerceptionTrigger->OnComponentEndOverlap.AddDynamic(this, &ATower::OnEndOverlap);
	PerceptionTrigger->SetupAttachment(Visuals);
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("Sound Cue");
	if (towerLvl1Sounds.Succeeded()) AudioComponent->SetSound(towerLvl1Sounds.Object);
	AudioComponent->SetupAttachment(Visuals);

	auto bullet = ConstructorHelpers::FClassFinder<ABullet>(*BULLET_PATH);
	if (bullet.Succeeded()) BulletClass = bullet.Class;
	
	// Nav Modifier
	NavModComp = CreateDefaultSubobject<UNavModifierComponent>("Nav Modifier");
	NavModComp->SetAreaClass(ConstructorHelpers::FClassFinder<UNavArea>(*NAV_AREA_CLASS).Class);
	NavModComp->FailsafeExtent = FailsafeExtentSize;

	// Disable Nav Affect from other Components
	Visuals->SetCanEverAffectNavigation(false);
	PerceptionTrigger->SetCanEverAffectNavigation(false);
	AudioComponent->SetCanEverAffectNavigation(false);
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	if (AudioComponent) AudioComponent->Play();

	//Activate();

	SetStats();
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RotationSpeed != 0)
	{
		auto rotation = GetActorRotation();
		rotation.Add(0.0f, RotationSpeed * DeltaTime, 0.0f);
		SetActorRotation(rotation);
	}

	if (DoUpgrade)
	{
		DoUpgrade = false;
		Upgrade();
	}
}

void ATower::Activate(void)
{
	if (IsActive) return;

	IsActive = true;
	if (AudioComponent) AudioComponent->SetTriggerParameter("On Build");
}

void ATower::Upgrade(void)
{
	CurrentLvl++;

	SetStats();

	if (!AudioComponent->IsPlaying()) AudioComponent->Play();
}

void ATower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto enemy = Cast<AEnemy>(OtherActor); enemy)
	{
		EnemiesInRangeCounter++;
		if (EnemiesInRangeCounter == 1)
		{
			GWorld->GetTimerManager().SetTimer(AttackTimerHandle, this, &ATower::SpawnBullet, 1.0f / FireRate, true, -1.0f);
		}
	}
}

void ATower::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto enemy = Cast<AEnemy>(OtherActor); enemy)
	{
		EnemiesInRangeCounter--;
		if (EnemiesInRangeCounter == 0)
		{
			GWorld->GetTimerManager().ClearTimer(AttackTimerHandle);
		}
	}
}

void ATower::SetStats(void)
{
	switch (CurrentLvl)
	{
	case 1:
		AttentionRadius = LVL_ONE_ATTENTION_RADIUS;
		if (PerceptionTrigger) PerceptionTrigger->SetSphereRadius(AttentionRadius);

		FireRate = LVL_ONE_FIRE_RATE;

		RotationSpeed = LVL_ONE_ROTATION_SPEED;

		BulletDamage = LVL_ONE_BULLET_DAMAGE;

		if (lvlOneMesh) Visuals->SetStaticMesh(lvlOneMesh);
		break;

	case 2:
		AttentionRadius = LVL_TWO_ATTENTION_RADIUS;
		if (PerceptionTrigger) PerceptionTrigger->SetSphereRadius(AttentionRadius);

		FireRate = LVL_TWO_FIRE_RATE;

		RotationSpeed = LVL_TWO_ROTATION_SPEED;

		BulletDamage = LVL_TWO_BULLET_DAMAGE;

		if (lvlTwoMesh) Visuals->SetStaticMesh(lvlTwoMesh);
		break;

	case 3:
		AttentionRadius = LVL_THREE_ATTENTION_RADIUS;
		if (PerceptionTrigger) PerceptionTrigger->SetSphereRadius(AttentionRadius);

		FireRate = LVL_THREE_FIRE_RATE;

		RotationSpeed = LVL_THREE_ROTATION_SPEED;

		BulletDamage = LVL_THREE_BULLET_DAMAGE;

		if (lvlThreeMesh) Visuals->SetStaticMesh(lvlThreeMesh);
		break;

	default:
		break;
	}
}

void ATower::SpawnBullet(void)
{
	if (BulletClass)
	{
		if (AudioComponent) AudioComponent->SetTriggerParameter("On Shoot");
		auto bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, GetActorLocation() + FVector::UpVector * 125, GetActorRotation());
		bullet->Init(BulletMoveSpeed, BulletDamage, EBulletMeshType::BMT_Default);
	}
}