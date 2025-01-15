// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Shed.generated.h"

UCLASS()
class AShed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShed();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FVector GetEnemyTargetPos() { return GetActorLocation() + EnemyTarget->GetRelativeLocation(); }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TakeDamage(int dmg);

private:
	// Paths
	const FString MESH_PATH = "/Script/Engine.StaticMesh'/Game/SnowedIn/Meshes/SM_LogCabin.SM_LogCabin'";
	const FString MAT_PATH = "/Script/Engine.MaterialInstanceConstant'/Game/SnowedIn/Materials/MI_Shed.MI_Shed'";

	const FString ENEMY_TRIGGER_COLL_NAME = "OverlapAllDynamic";

	const FVector EnemyTargetPos = FVector(-200, 0, 0);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Components
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent* EnemyTarget = nullptr;

	UPROPERTY(EditAnywhere)
	UBoxComponent* EnemyTrigger = nullptr;

	UPROPERTY(EditAnywhere)
	int HP = 500;

	class UGameManager* GM = nullptr;
};
