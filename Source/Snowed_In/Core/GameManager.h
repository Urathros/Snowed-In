// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager.generated.h"

DECLARE_DELEGATE(FHandleIceCrystalsChangedSignature);

/**
 * 
 */
UCLASS(BlueprintType)
class SNOWED_IN_API UGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	static auto GetGameInstance(const UObject& a_target) -> UGameInstance* const;
public:

	// Get the Game Manager with this
	static auto Instantiate(const UObject& a_target) -> UGameManager* const;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize();

	/*************************************************************************/
	#pragma region Getter/Setter
	/*************************************************************************/

	// Check if the Game is Paused
	auto GetPause(void) const -> const bool;

	// (Un)set the Game paused.
	auto SetPause(const bool& a_bPause) -> UGameManager&;


	// Get the current Number of Ice crystals
	auto GetIceCrystals(void) const -> const uint32;

	// Set the current Number of Ice crystalls
	auto SetIceCrystals(const uint32& a_IceCrystals) -> UGameManager&;

	// Add a number of ice crystals to the counter
	auto AddIceCrystals(const uint32& a_IceCrystals) -> UGameManager&;

	// Substract a number of ice crystals to the counter
	auto SubstractIceCrystals(const uint32& a_IceCrystals) -> UGameManager&;

	// Increment the ice crystal counter
	auto IncrementIceCrystals(void) -> UGameManager&;

	// Decrement the ice crystal counter
	auto DecrementIceCrystals(void) -> UGameManager&;

	#pragma endregion
	/*************************************************************************/
private:
	/*************************************************************************/
	#pragma region MemberVariables
	/*************************************************************************/

	// Controlls if the game is paused.
	bool bPause = false;

	// Counter of global ice crystals
	uint32 IceCrystals = 0;


	#pragma endregion
	/*************************************************************************/

public:
	FHandleIceCrystalsChangedSignature HandleIceCrystalsChangedDelegate = nullptr;
};
