// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/CoreBlueprintFunctionLibrary.h"
#include "../Core/GameManager.h"

/*****************************************************************************/
// Game Manager
/*****************************************************************************/
// Get Paused
/*****************************************************************************/
const bool UCoreBlueprintFunctionLibrary::GetPaused(const UObject* a_GameObject)
{
	/*-----------------------------------------------------------------------*/
	// nullptr exception
	/*-----------------------------------------------------------------------*/
	if (a_GameObject == nullptr)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Game Object of Get Paused was a Nullptr Exception."));

		return false;
	}
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// connect to GM
	/*-----------------------------------------------------------------------*/
	UGameManager* pGameManager = UGameManager::Instantiate(*a_GameObject);
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// Get Pause
	/*-----------------------------------------------------------------------*/
	return pGameManager->GetPause();
	/*-----------------------------------------------------------------------*/
}
/*****************************************************************************/



/*****************************************************************************/
// Set Paused
/*****************************************************************************/
void UCoreBlueprintFunctionLibrary::SetPaused(const bool a_bPause,
	const UObject* a_GameObject)
{
	/*-----------------------------------------------------------------------*/
	// nullptr exception
	/*-----------------------------------------------------------------------*/
	if (a_GameObject == nullptr)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Game Object of Set Paused was a Nullptr Exception."));

		return;
	}
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// connect to GM
	/*-----------------------------------------------------------------------*/
	UGameManager* pGameManager = UGameManager::Instantiate(*a_GameObject);
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// Set Pause
	/*-----------------------------------------------------------------------*/
	pGameManager->SetPause( a_bPause);
	/*-----------------------------------------------------------------------*/
}



const int UCoreBlueprintFunctionLibrary::GetIceCrystals(const UObject* a_GameObject)
{
	/*-----------------------------------------------------------------------*/
	// nullptr exception
	/*-----------------------------------------------------------------------*/
	if (a_GameObject == nullptr)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Game Object of Get Paused was a Nullptr Exception."));

		return false;
	}
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// connect to GM
	/*-----------------------------------------------------------------------*/
	UGameManager* pGameManager = UGameManager::Instantiate(*a_GameObject);
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// Get Ice Crystals
	/*-----------------------------------------------------------------------*/
	return static_cast<int>(pGameManager->GetIceCrystals());
	/*-----------------------------------------------------------------------*/
}



void UCoreBlueprintFunctionLibrary::SetIceCrystals(const int a_IceCrystals, const UObject* a_GameObject)
{
	/*-----------------------------------------------------------------------*/
	// nullptr exception
	/*-----------------------------------------------------------------------*/
	if (a_GameObject == nullptr)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Game Object of Set Paused was a Nullptr Exception."));

		return;
	}
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// connect to GM
	/*-----------------------------------------------------------------------*/
	UGameManager* pGameManager = UGameManager::Instantiate(*a_GameObject);
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// Set Ice Crystals
	/*-----------------------------------------------------------------------*/
	pGameManager->SetIceCrystals(a_IceCrystals);
	/*-----------------------------------------------------------------------*/
}



void UCoreBlueprintFunctionLibrary::AddIceCrystals(const int a_IceCrystals, const UObject* a_GameObject)
{
	/*-----------------------------------------------------------------------*/
	// nullptr exception
	/*-----------------------------------------------------------------------*/
	if (a_GameObject == nullptr)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Game Object of Set Paused was a Nullptr Exception."));

		return;
	}
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// connect to GM
	/*-----------------------------------------------------------------------*/
	UGameManager* pGameManager = UGameManager::Instantiate(*a_GameObject);
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// Add Ice Crystals
	/*-----------------------------------------------------------------------*/
	pGameManager->AddIceCrystals(a_IceCrystals);
	/*-----------------------------------------------------------------------*/
}



void UCoreBlueprintFunctionLibrary::SubstractIceCrystals(const int a_IceCrystals, const UObject* a_GameObject)
{
	/*-----------------------------------------------------------------------*/
	// nullptr exception
	/*-----------------------------------------------------------------------*/
	if (a_GameObject == nullptr)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Game Object of Set Paused was a Nullptr Exception."));

		return;
	}
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// connect to GM
	/*-----------------------------------------------------------------------*/
	UGameManager* pGameManager = UGameManager::Instantiate(*a_GameObject);
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// Substract Ice Crystals
	/*-----------------------------------------------------------------------*/
	pGameManager->SubstractIceCrystals(a_IceCrystals);
	/*-----------------------------------------------------------------------*/
}



void UCoreBlueprintFunctionLibrary::IncrementIceCrystals(const UObject* a_GameObject)
{
	/*-----------------------------------------------------------------------*/
	// nullptr exception
	/*-----------------------------------------------------------------------*/
	if (a_GameObject == nullptr)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Game Object of Set Paused was a Nullptr Exception."));

		return;
	}
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// connect to GM
	/*-----------------------------------------------------------------------*/
	UGameManager* pGameManager = UGameManager::Instantiate(*a_GameObject);
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// Increment Ice Crystals
	/*-----------------------------------------------------------------------*/
	pGameManager->IncrementIceCrystals();
	/*-----------------------------------------------------------------------*/
}



void UCoreBlueprintFunctionLibrary::DecrementIceCrystals(const UObject* a_GameObject)
{
	/*-----------------------------------------------------------------------*/
	// nullptr exception
	/*-----------------------------------------------------------------------*/
	if (a_GameObject == nullptr)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Game Object of Set Paused was a Nullptr Exception."));

		return;
	}
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// connect to GM
	/*-----------------------------------------------------------------------*/
	UGameManager* pGameManager = UGameManager::Instantiate(*a_GameObject);
	/*-----------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------*/
	// Decrement Ice Crystals
	/*-----------------------------------------------------------------------*/
	pGameManager->DecrementIceCrystals();
	/*-----------------------------------------------------------------------*/
}
/*****************************************************************************/