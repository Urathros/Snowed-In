// Fill out your copyright notice in the Description page of Project Settings.


#include "../Bullets/Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Enemy/Enemy.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	Collision->SetSphereRadius(CollisionRadius);
	Collision->SetCollisionProfileName(*DEFAULT_COLLISION_PROFILE_NAME);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnCollision);
	SetRootComponent(Collision);

	Visual = CreateDefaultSubobject<UStaticMeshComponent>("Visuals");
	Visual->SetRelativeScale3D(MeshScale);
	Visual->SetRelativeRotation(MeshRotation);
	Visual->SetupAttachment(Collision);

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	Projectile->InitialSpeed = MoveSpeed;
	Projectile->ProjectileGravityScale = 0;

	auto parts = ConstructorHelpers::FObjectFinder<UNiagaraSystem>(*PARTICLES_PATH);
	if (parts.Succeeded()) Particles = parts.Object;

	auto defaultMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(*DEFAULT_MESH_PATH);
	if (defaultMesh.Succeeded()) DefaultMeshPtr = defaultMesh.Object;
	auto carrotMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(*CARROT_MESH_PATH);
	if (carrotMesh.Succeeded()) CarrotMeshPtr = carrotMesh.Object;

	auto defaultMat = ConstructorHelpers::FObjectFinder<UMaterialInstance>(*DEFAULT_MAT_PATH);
	if (defaultMat.Succeeded()) DefaultMatPtr = defaultMat.Object;
	auto carrotMat = ConstructorHelpers::FObjectFinder<UMaterialInstance>(*CARROT_MAT_PATH);
	if (carrotMat.Succeeded()) CarrotMatPtr = carrotMat.Object;
}

void ABullet::Init(float a_moveSpeed, int32 a_dmg, EBulletMeshType a_meshType)
{
	MoveSpeed = a_moveSpeed;
	Damage = a_dmg;

	FVector vel = FVector::RightVector * MoveSpeed;
	Projectile->Velocity = GetActorRotation().RotateVector(vel);

	InitMesh(a_meshType);
}

void ABullet::InitMesh(EBulletMeshType a_meshType)
{
	if (!Visual) return;

	TObjectPtr<UStaticMesh> mesh = {};
	TObjectPtr<UMaterialInstance> mat = {};
	switch (a_meshType)
	{
	case EBulletMeshType::BMT_Default:
		mesh = DefaultMeshPtr;
		mat = DefaultMatPtr;
		break;

	case EBulletMeshType::BMT_Carrot:
		mesh = CarrotMeshPtr;
		mat = CarrotMatPtr;
		break;

	default:
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Case not implemented");
		break;
	}

	Visual->SetStaticMesh(mesh);
	Visual->SetMaterial(0, mat);
}

void ABullet::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto enemy = Cast<AEnemy>(OtherActor); enemy)
	{
		enemy->TakeDamage(Damage);
		//TODO: Put Destroy on Delay (make mesh invisible instead)
		Destroy();
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	if (Particles)
	{
		auto NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			Particles, Visual, NAME_None, FVector(0.f), FRotator(-90.f, 0.f, 0.f), EAttachLocation::KeepRelativeOffset, true);
	}
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}