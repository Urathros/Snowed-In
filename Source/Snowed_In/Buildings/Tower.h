// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

UCLASS()
class ATower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Activate(void);

private:
	bool IsActive = false;

	const FString MESH_PATH = "/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'";
	const FString MAT_PATH = "/Script/Engine.Material'/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial'";

	const FString BULLET_PATH = "/Script/CoreUObject.Class'/Script/Snowed_In.Bullet'";

	const FString DEFAULT_COLLISION_PROFILE_NAME = "OverlapAllDynamic";

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SpawnBullet(void);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Visuals = nullptr;

	UPROPERTY(EditAnywhere)
	class USphereComponent* PerceptionTrigger = nullptr;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float AttentionRadius = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Stats|Bullet")
	int32 BulletDamage = 1;

	UPROPERTY(EditAnywhere, Category = "Stats|Bullet")
	int32 BulletMoveSpeed = 1000;

	UPROPERTY(EditAnywhere, Category = "Stats")
	int EnemiesInRangeCounter = 0;
	FTimerHandle AttackTimerHandle = {};

	TSubclassOf<class ABullet> BulletClass = {};
};