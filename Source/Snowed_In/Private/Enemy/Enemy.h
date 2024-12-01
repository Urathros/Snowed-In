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

	bool TakeDamage(int32 Dmg);
	int32 GetHealth(void);
	void Die(void);

private:
	// Paths
	const FString MESH_ONE_PATH = "/Script/Engine.SkeletalMesh'/Game/SnowedIn/Meshes/Enemies/buttnmandl.buttnmandl'";
	const FString MESH_TWO_PATH = "/Script/Engine.SkeletalMesh'/Game/SnowedIn/Meshes/Enemies/SKM_Witch_Edeltraud.SKM_Witch_Edeltraud'";
	const FString MESH_THREE_PATH = "/Script/Engine.SkeletalMesh'/Game/SnowedIn/Meshes/Enemies/SMK_Krampus.SMK_Krampus'";

	const FString MAT_ONE_PATH = "MaterialInstanceConstant'/Game/SnowedIn/Materials/MI_Buttnmandl'";
	const FString MAT_TWO_PATH = "/Script/Engine.Material'/Game/Characters/Mannequins/Materials/M_Mannequin.M_Mannequin'";
	const FString MAT_THREE_PATH = "/Script/Engine.MaterialInstanceConstant'/Game/SnowedIn/Materials/MI_Krampus.MI_Krampus'";
	const FString CONTROLLER_PATH = "/Script/CoreUObject.Class'/Script/Snowed_In.EnemyController'";

	const float MOVE_SPEED = 200.0f;
	const float SLOWED_MOVE_SPEED = 75.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	int32 HP = 1;

	class UGameManager* GM = nullptr;
};
