// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/EnemyController.h"
#include "Shed.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto mesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(*MESH_PATH);
	auto mat = ConstructorHelpers::FObjectFinder<UMaterialInstance>(*MAT_PATH);

	if (mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(mesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	}
	if (mat.Succeeded()) GetMesh()->SetMaterial(0, mat.Object);

	auto controller = ConstructorHelpers::FClassFinder<AEnemyController>(*CONTROLLER_PATH);
	if (controller.Succeeded()) AIControllerClass = AEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = MOVE_SPEED;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle handle = {};
	if (const auto ShedActor = UGameplayStatics::GetActorOfClass(GWorld, AShed::StaticClass()); ShedActor)
	{
		if (const auto Shed = Cast<AShed>(ShedActor); Shed)
		{
			if (auto ctrl = GetController<AEnemyController>(); ctrl) ctrl->MoveToPoint(Shed->GetEnemyTargetPos());
			else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "No Controller (of type AEnemyController");
		}
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AEnemy::TakeDamage(int32 Dmg)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Magenta, FString::Printf(TEXT("%s took %d damage"), *GetName(), Dmg));
	HP = FMath::Clamp(HP - Dmg, 0, HP);
	if (HP == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%s died"), *GetName()));
		//TODO: Add Particles and put Destroy on Delay (make mesh invisible instead)
		Destroy();
		return true;
	}

	return false;
}
