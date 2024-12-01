// Fill out your copyright notice in the Description page of Project Settings.


#include "Shed.h"
#include "../Private/Enemy/Enemy.h"
#include "../Core/GameManager.h"

// Sets default values
AShed::AShed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_PATH);
	auto mat = ConstructorHelpers::FObjectFinder<UMaterialInstance>(*MAT_PATH);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Visuals");
	SetRootComponent(MeshComp);
	if (mesh.Succeeded()) MeshComp->SetStaticMesh(mesh.Object);
	if (mat.Succeeded()) MeshComp->SetMaterial(0, mat.Object);

	EnemyTarget = CreateDefaultSubobject<USceneComponent>("EnemyTarget");
	EnemyTarget->SetRelativeLocation(EnemyTargetPos);
	EnemyTarget->SetupAttachment(MeshComp);

	EnemyTrigger = CreateDefaultSubobject<UBoxComponent>("EnemyTrigger");
	EnemyTrigger->SetRelativeLocation(FVector(0, 0, 200));
	EnemyTrigger->SetBoxExtent(FVector(600, 600, 400));
	EnemyTrigger->SetCollisionProfileName(*ENEMY_TRIGGER_COLL_NAME);
	EnemyTrigger->OnComponentBeginOverlap.AddDynamic(this, &AShed::OnBeginOverlap);
	EnemyTrigger->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AShed::BeginPlay()
{
	Super::BeginPlay();
	
	GM = UGameManager::Instantiate(*this);
}

// Called every frame
void AShed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShed::TakeDamage(int dmg)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Shed took %d damage"), dmg));
	HP = FMath::Clamp(HP - dmg, 0, HP);
	if (HP == 0)
	{
		GM->InvokeGameOver();
	}
}

void AShed::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, OtherActor->GetName());
	if (auto enemy = Cast<AEnemy>(OtherActor); enemy)
	{
		TakeDamage(enemy->GetHealth());
		enemy->Die();
	}
}
