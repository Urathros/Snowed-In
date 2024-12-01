// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "../Snowed_InCharacter.h"
#include "../Core/GameManager.h"
#include "IceCrystal.generated.h"

UCLASS()
class SNOWED_IN_API AIceCrystal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIceCrystal();
	virtual void InitializeCrystal(int a_CrystalValue, float a_CrystalLifetime, float a_ReductionDelay);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	// Functions
	UFUNCTION()
	void EventHit(UPrimitiveComponent* a_pOverlappedComponent, AActor* a_pOtherActor,
					UPrimitiveComponent* a_pOtherComp, int32 a_OtherBodyIndex, bool bFromSweep,
					const FHitResult& a_SweepResult);

	void ReduceValue();


	// Components
	UGameManager* GM = nullptr;
	FTimerHandle ValueTimerHandle;
	FTimerHandle LifeSpanTimerHandle;
	USphereComponent* CrystalMeshBounds = nullptr;
	USphereComponent* CrystalHitbox = nullptr;
	UStaticMeshComponent* SMCrystal = nullptr;

	// Variables
	int Value = 10;
	float Lifetime = 10.0f;
	float ReductionDelay = 1.0f;
	FVector RotationSpeed = FVector(0.0f, 50.0f, 50.0f);
	float AlphaHeight = 10.0f;
	float RunningTime = 0.0f;

	// Constants
	const float CRYSTAL_MESH_BOUND_SIZE = 50.0f;
	const float CRYSTAL_HITBOX_SIZE = 55.0f;
	FString SM_CRYSTAL_PATH = TEXT("/Script/Engine.StaticMesh'/Game/SnowedIn/Meshes/SM_IceCrystal.SM_IceCrystal'");
};