// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void GoToShed(void);

	// Paths
	const FString MESH_PATH = "/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple'";
	const FString MAT_PATH = "/Script/Engine.Material'/Game/Characters/Mannequins/Materials/M_Mannequin.M_Mannequin'";
	const FString CONTROLLER_PATH = "/Script/CoreUObject.Class'/Script/Snowed_In.EnemyController'";

	const float MOVE_SPEED = 200.0f;
	const float SLOWED_MOVE_SPEED = 75.0f;
};
