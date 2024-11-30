// Fill out your copyright notice in the Description page of Project Settings.


#include "../Buildings/DummyBuilding.h"


const FString ADummyBuilding::MESH_NAME = FString(TEXT("Mesh Component"));

// Sets default values
ADummyBuilding::ADummyBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>(*MAT_REF_PATH).Object;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(*MESH_NAME);

	Mesh->SetupAttachment(RootComponent);
	Mesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_REF_PATH).Object);
	Mesh->SetMaterial(0, Material);

	bMoveable = true;
}

// Called when the game starts or when spawned
void ADummyBuilding::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerController = GetWorld()->GetFirstPlayerController(); !PlayerController) return;
}

// Called every frame
void ADummyBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bMoveable) return; 
	if (PlayerController) PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	SetActorLocation(MouseLocation);
	SetActorRotation(FRotator::MakeFromEuler(MouseDirection));
}

