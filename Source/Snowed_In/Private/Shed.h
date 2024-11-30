// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

private:
	// Paths
	const FString MESH_PATH = "/Script/Engine.StaticMesh'/Game/SnowedIn/Meshes/SM_LogCabin.SM_LogCabin'";
	const FString MAT_PATH = "/Script/Engine.Material'/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial'";

	const FVector EnemyTargetPos = FVector(-200, 0, 0);

	// Components
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent* EnemyTarget = nullptr;
};
