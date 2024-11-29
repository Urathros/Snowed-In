// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/GameManager.h"
#include <Kismet/GameplayStatics.h>

auto UGameManager::GetGameInstance(const UObject& a_target) -> UGameInstance* const
{
	if (a_target.GetWorld() && a_target.GetWorld()->GetGameInstance())
	{
		return UGameplayStatics::GetGameInstance(a_target.GetWorld());
	}
	else if (a_target.IsA(AActor::StaticClass()))
	{
		if (Cast<AActor>(&a_target)->GetGameInstance()) return GEngine->GetWorld()->GetGameInstance();
	}
	return nullptr;
}

auto UGameManager::Instantiate(const UObject& a_target) -> UGameManager* const
{
	auto instance = GetGameInstance(a_target);
	if (instance) return instance->GetSubsystem<UGameManager>();

	return nullptr;
}

void UGameManager::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Display, TEXT("Game Manager initialized."));
}

void UGameManager::Deinitialize()
{
	UE_LOG(LogTemp, Display, TEXT("Game Manager finalized."));
}

auto UGameManager::GetPause() const -> const bool
{
	return bPause;
}

auto UGameManager::SetPause(const bool& a_bPause) -> UGameManager&
{
	bPause = a_bPause;
	return *this;
}

auto UGameManager::GetIceCrystals(void) const -> const uint32
{
	return IceCrystals;
}

auto UGameManager::SetIceCrystals(const uint32& a_IceCrystals) -> UGameManager&
{
	IceCrystals = a_IceCrystals;
	return *this;
}

auto UGameManager::AddIceCrystals(const uint32& a_IceCrystals) -> UGameManager&
{
	IceCrystals += a_IceCrystals;
	return *this;
}

auto UGameManager::SubstractIceCrystals(const uint32& a_IceCrystals) -> UGameManager&
{
	IceCrystals -= a_IceCrystals;
	return *this;
}

auto UGameManager::IncrementIceCrystals(void) -> UGameManager&
{
	IceCrystals++;
	return *this;
}

auto UGameManager::DecrementIceCrystals(void) -> UGameManager&
{
	IceCrystals--;
	return *this;
}
