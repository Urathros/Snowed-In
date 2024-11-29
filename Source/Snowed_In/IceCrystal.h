// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "IceCrystal.generated.h"

UCLASS()
class SNOWED_IN_API AIceCrystal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIceCrystal();
	virtual void InitializeCrystal(int a_CrystalValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	// Components
	UPROPERTY(EditAnywhere, Category = "Components")
	USphereComponent* CrystalHitbox;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* SMCrystal;

	// Properties
	UPROPERTY(EditAnywhere, Category = "Attributes")
	int Value = 10;

	// Constants
	const float CRYSTAL_HITBOX_SIZE = 1.0f;
	FString SM_CRYSTAL_PATH = TEXT("/Script/Engine.StaticMesh'/Game/SnowedIn/Meshes/SM_Crystal_PlaceHolder.SM_Crystal_PlaceHolder'");
};
