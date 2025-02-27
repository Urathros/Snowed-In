// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	void MoveToPoint(const FVector& point);
};
