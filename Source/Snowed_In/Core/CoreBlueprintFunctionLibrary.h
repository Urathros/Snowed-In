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
	// Get Pause of GameManager
	UFUNCTION( BlueprintCallable, 
			   meta = ( DisplayName = "Get Paused", Category = "Core" ) )
		static const bool GetPaused( const UObject* a_GameObject );

	// Set Pause of GameManager
	UFUNCTION( BlueprintCallable, 
			   meta = ( DisplayName = "Set Paused", Category = "Core" ) )
		static void SetPaused(  const bool _IsPaused, 
								const UObject* a_GameObject );
	
	
	// Get the Ice Crystals in Game Manager
	UFUNCTION( BlueprintCallable, 
			   meta = ( DisplayName = "Get Ice Crystals", Category = "Core" ) )
		static const int GetIceCrystals( const UObject* a_GameObject );

	// Set the Ice Crystals in Game Manager
	UFUNCTION( BlueprintCallable, 
			   meta = ( DisplayName = "Set Ice Crystals", Category = "Core" ) )
		static void SetIceCrystals(  const int a_IceCrystals,
									 const UObject* a_GameObject );
		
	// Add a Number of Ice Crystals to the Counter in Game Manager
	UFUNCTION( BlueprintCallable, 
			   meta = ( DisplayName = "Add Ice Crystals", Category = "Core" ) )
		static void AddIceCrystals( const int a_IceCrystals,
									const UObject* a_GameObject );
	// Substract a Number of Ice Crystals to the Counter in the Game Manager
	UFUNCTION( BlueprintCallable, 
			   meta = ( DisplayName = "Substract Ice Crystals", Category = "Core" ) )
		static void SubstractIceCrystals( const int a_IceCrystals,
										  const UObject* a_GameObject );

	// Increment the Counter in the Game Manager
	UFUNCTION( BlueprintCallable,
			   meta = ( DisplayName = "Increment Ice Crystals", Category = "Core" ) )
		static void IncrementIceCrystals(const UObject* a_GameObject);

	// Decrement the Counter in the Game Manager
	UFUNCTION(	BlueprintCallable,
				meta = (DisplayName = "Decrement Ice Crystals", Category = "Core"))
		static void DecrementIceCrystals(const UObject* a_GameObject);
};
