// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

enum class EBulletMeshType
{
	BMT_Default,
	BMT_Carrot,
};

UCLASS()
class SNOWED_IN_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	void Init(float a_moveSpeed, int32 a_dmg, EBulletMeshType a_meshType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void InitMesh(EBulletMeshType a_meshType);

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	const FString DEFAULT_MESH_PATH = "/Script/Engine.StaticMesh'/Engine/BasicShapes/Cone.Cone'";
	const FString CARROT_MESH_PATH = "/Script/Engine.StaticMesh'/Engine/BasicShapes/Cone.Cone'";

	const FString DEFAULT_MAT_PATH = "/Script/Engine.Material'/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial'";
	const FString CARROT_MAT_PATH = "/Script/Engine.Material'/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial'";

	const FString DEFAULT_COLLISION_PROFILE_NAME = "OverlapAllDynamic";

	const float CollisionRadius = 50;
	const FVector MeshScale = FVector(0.1f, 0.1f, 0.1f);
	const FRotator MeshRotation = FRotator(-90, 0, 0);

	float MoveSpeed = 0.0f;
	int32 Damage = 1;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Visual = nullptr;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Collision = nullptr;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* Projectile = nullptr;

	TObjectPtr<UStaticMesh> DefaultMeshPtr = {};
	TObjectPtr<UStaticMesh> CarrotMeshPtr = {};
	TObjectPtr<UMaterialInstance> DefaultMatPtr = {};
	TObjectPtr<UMaterialInstance> CarrotMatPtr = {};
};
