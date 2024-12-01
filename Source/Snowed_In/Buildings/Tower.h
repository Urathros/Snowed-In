// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavModifierComponent.h"
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
	void Upgrade(void);

	FORCEINLINE int32 GetCurrentLevel(void) { return CurrentLvl; }

private:
	bool IsActive = false;

	const FString MESH_LVL1_PATH = "/Script/Engine.StaticMesh'/Game/SnowedIn/Meshes/Towers/SMK_Snowman_Gang_GameJam_SnowMan_Bene_Lvl1.SMK_Snowman_Gang_GameJam_SnowMan_Bene_Lvl1'";
	const FString MESH_LVL2_PATH = "/Script/Engine.StaticMesh'/Game/SnowedIn/Meshes/Towers/SMK_Snowman_Gang_GameJam_SnowMan_Nepomuk_Lvl2.SMK_Snowman_Gang_GameJam_SnowMan_Nepomuk_Lvl2'";
	const FString MESH_LVL3_PATH = "/Script/Engine.StaticMesh'/Game/SnowedIn/Meshes/Towers/SMK_Snowman_Gang_GameJam_Snowman_Sepp_Lvl3.SMK_Snowman_Gang_GameJam_Snowman_Sepp_Lvl3'";
	const FString MAT_PATH = "/Script/Engine.MaterialInstanceConstant'/Game/SnowedIn/Materials/MI_Snowman_Gang.MI_Snowman_Gang'";

	const FString TOWER_LVL1_SFX_PATH = "/Script/MetasoundEngine.MetaSoundSource'/Game/SnowedIn/Audio/MetaSounds/MS_TowerLvlOne.MS_TowerLvlOne'";
	const FString TOWER_LVL2_SFX_PATH = "/Script/MetasoundEngine.MetaSoundSource'/Game/SnowedIn/Audio/MetaSounds/MS_TowerLvlTwo.MS_TowerLvlTwo'";
	const FString TOWER_LVL3_SFX_PATH = "/Script/MetasoundEngine.MetaSoundSource'/Game/SnowedIn/Audio/MetaSounds/MS_TowerLvlThree.MS_TowerLvlThree'";

	const FString BULLET_PATH = "/Script/CoreUObject.Class'/Script/Snowed_In.Bullet'";

	const FString DEFAULT_COLLISION_PROFILE_NAME = "OverlapAllDynamic";

	const FString NAV_AREA_CLASS = "/Script/CoreUObject.Class'/Script/NavigationSystem.NavArea_Null'";

#pragma region Level Stats
	const float LVL_ONE_ATTENTION_RADIUS = 1000.0f;
	const float LVL_TWO_ATTENTION_RADIUS = 1000.0f;
	const float LVL_THREE_ATTENTION_RADIUS = 500.0f;

	const float LVL_ONE_FIRE_RATE = 1.0f;
	const float LVL_TWO_FIRE_RATE = 2.0f;
	const float LVL_THREE_FIRE_RATE = 5.0f;

	const float LVL_ONE_ROTATION_SPEED = 0.0f;
	const float LVL_TWO_ROTATION_SPEED = 0.0f;
	const float LVL_THREE_ROTATION_SPEED = 75.0f;

	const int32 LVL_ONE_BULLET_DAMAGE = 1;
	const int32 LVL_TWO_BULLET_DAMAGE = 1;
	const int32 LVL_THREE_BULLET_DAMAGE = 1;
#pragma endregion

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetStats(void);
	void SpawnBullet(void);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Visuals = nullptr;

	UPROPERTY(EditAnywhere)
	class USphereComponent* PerceptionTrigger = nullptr;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float AttentionRadius = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float RotationSpeed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Stats|Bullet")
	int32 BulletDamage = 1;

	UPROPERTY(EditAnywhere, Category = "Stats|Bullet")
	int32 BulletMoveSpeed = 1000;

	UPROPERTY(EditAnywhere, Category = "Stats")
	bool DoUpgrade = false;

	UPROPERTY(EditAnywhere, Category = "Stats")
	int32 StartLvl = 1;

	UPROPERTY(EditAnywhere, Category = "Stats")
	int EnemiesInRangeCounter = 0;
	FTimerHandle AttackTimerHandle = {};

	UPROPERTY(EditAnywhere, Category = "Components")
	class UNavModifierComponent* NavModComp = nullptr;

	FVector FailsafeExtentSize = FVector(50.0f, 50.0f, 50.0f);

	int32 CurrentLvl = 1;

	TSubclassOf<class ABullet> BulletClass = {};

	USoundBase* lvlOneSounds = nullptr;
	USoundBase* lvlTwoSounds = nullptr;
	USoundBase* lvlThreeSounds = nullptr;

	UStaticMesh* lvlOneMesh = nullptr;
	UStaticMesh* lvlTwoMesh = nullptr;
	UStaticMesh* lvlThreeMesh = nullptr;
};