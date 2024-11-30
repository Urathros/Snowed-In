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
	if (const auto shed = UGameplayStatics::GetActorOfClass(GWorld, AShed::StaticClass()); shed)
	{
		if (auto ctrl = GetController<AEnemyController>(); ctrl) ctrl->MoveToPoint(shed->GetActorLocation());
		else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "No Controller (of type AEnemyController");
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