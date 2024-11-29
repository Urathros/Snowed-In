// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager.generated.h"

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
	auto GetPause() const -> const bool;

	// (Un)set the Game paused.
	auto SetPause(const bool& a_bPause) -> UGameManager&;

	#pragma endregion
	/*************************************************************************/
private:
	/*************************************************************************/
	#pragma region MemberVariables
	/*************************************************************************/

	// Controlls if the game is paused.
	bool bPause = false;

	#pragma endregion
	/*************************************************************************/
};
