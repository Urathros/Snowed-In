// Fill out your copyright notice in the Description page of Project Settings.


#include "Shed.h"

// Sets default values
AShed::AShed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_PATH);
	auto mat = ConstructorHelpers::FObjectFinder<UMaterialInstance>(*MAT_PATH);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>("Visuals");
	SetRootComponent(meshComp);
	if (mesh.Succeeded()) meshComp->SetStaticMesh(mesh.Object);
	if (mat.Succeeded()) meshComp->SetMaterial(0, mat.Object);
}

// Called when the game starts or when spawned
void AShed::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

