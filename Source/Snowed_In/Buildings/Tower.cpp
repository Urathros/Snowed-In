// Fill out your copyright notice in the Description page of Project Settings.


#include "../Buildings/Tower.h"
#include "Components/SphereComponent.h"
#include "Enemy/Enemy.h"
#include "../Bullets/Bullet.h"

// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_PATH);
	auto mat = ConstructorHelpers::FObjectFinder<UMaterialInstance>(*MAT_PATH);

	Visuals = CreateDefaultSubobject<UStaticMeshComponent>("Visuals");
	if (mesh.Succeeded()) Visuals->SetStaticMesh(mesh.Object);
	if (mat.Succeeded()) Visuals->SetMaterial(0, mat.Object);
	SetRootComponent(Visuals);

	PerceptionTrigger = CreateDefaultSubobject<USphereComponent>("Perception Trigger");
	PerceptionTrigger->SetSphereRadius(AttentionRadius);
	PerceptionTrigger->SetCollisionProfileName(*DEFAULT_COLLISION_PROFILE_NAME);
	PerceptionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnBeginOverlap);
	PerceptionTrigger->OnComponentEndOverlap.AddDynamic(this, &ATower::OnEndOverlap);
	PerceptionTrigger->SetupAttachment(Visuals);

	auto bullet = ConstructorHelpers::FClassFinder<ABullet>(*BULLET_PATH);
	if (bullet.Succeeded()) BulletClass = bullet.Class;
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	Activate();

	if (PerceptionTrigger) PerceptionTrigger->SetSphereRadius(AttentionRadius);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATower::Activate(void)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, FString::Printf(TEXT("%s is now active"), *GetName()));
	IsActive = true;
}

void ATower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, FString::Printf(TEXT("%s collided with %s"), *GetName(), *OtherActor->GetName()));
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
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, FString::Printf(TEXT("%s End Overlap"), *OtherActor->GetName()));
	if (auto enemy = Cast<AEnemy>(OtherActor); enemy)
	{
		EnemiesInRangeCounter--;
		if (EnemiesInRangeCounter == 0)
		{
			GWorld->GetTimerManager().ClearTimer(AttackTimerHandle);
		}
	}
}

void ATower::SpawnBullet(void)
{
	if (BulletClass)
	{
		auto bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, GetActorLocation() + FVector::UpVector * 125, GetActorRotation());
		bullet->Init(BulletMoveSpeed, BulletDamage, EBulletMeshType::BMT_Default);
	}
}