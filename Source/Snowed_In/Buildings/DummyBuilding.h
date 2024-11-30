// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DummyBuilding.generated.h"

UCLASS()
class SNOWED_IN_API ADummyBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADummyBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	static const FString MESH_NAME;
	const FString MESH_REF_PATH = FString(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	const FString MAT_REF_PATH = FString(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));



	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (DisplayName = "Cube Mesh", Category = "Component", AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (DisplayName = "Cube Material", Category = "Component", AllowPrivateAccess = true))
	TObjectPtr<UMaterialInterface> Material = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Player Controller", Category = "System", AllowPrivateAccess = "true"))
	APlayerController* PlayerController = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Mouse Location", Category = "Movement", AllowPrivateAccess = "true"))
	FVector MouseLocation = FVector::Zero();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Mouse Direction", Category = "Movement", AllowPrivateAccess = "true"))
	FVector MouseDirection = FVector::Zero();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Moveable", Category = "Movement", AllowPrivateAccess = "true"))
	bool bMoveable = false;
};
