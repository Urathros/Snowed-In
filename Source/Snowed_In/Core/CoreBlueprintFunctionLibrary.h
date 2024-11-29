// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreBlueprintFunctionLibrary.generated.h"

//class SNOWED_IN_API UGameManager;

/**
 * 
 */
UCLASS()
class SNOWED_IN_API UCoreBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Get IsPaused of GameManager
	UFUNCTION( BlueprintCallable, 
			   meta = ( DisplayName = "Get Paused", Category = "Core" ) )
		static const bool GetPaused( const UObject* _GameObject );

	// Set IsPaused of GameManager
	UFUNCTION( BlueprintCallable, 
			   meta = ( DisplayName = "Set Paused", Category = "Core" ) )
		static void SetPaused(  const bool _IsPaused, 
								const UObject* _GameObject );
	
};
