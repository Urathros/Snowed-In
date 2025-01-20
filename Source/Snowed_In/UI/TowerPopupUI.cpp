// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/TowerPopupUI.h"
#include <Components/Button.h>
#include <../Buildings/Tower.h>
#include "../Core/GameManager.h"

const uint32 UTowerPopupUI::UPGRADE1_COST = 100;
const uint32 UTowerPopupUI::UPGRADE2_COST = 200;

UTowerPopupUI::UTowerPopupUI(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer) {}

void UTowerPopupUI::HandleIceCrystalsChanged()
{
	if (!GameManager) return;

	const auto&& iceCrystals = GameManager->GetIceCrystals();

	switch (CurrentBuilding->GetCurrentLevel())
	{

	case 1:

		if (UpgradeBtn) UpgradeBtn->SetIsEnabled(!(iceCrystals < UPGRADE1_COST));
		break;
	case 2:
		if (UpgradeBtn) UpgradeBtn->SetIsEnabled(!(iceCrystals < UPGRADE2_COST));
		break;
	case 3:
	default:
		break;
	}
}

void UTowerPopupUI::HandleUpdateButtonClicked()
{
	switch (CurrentBuilding->GetCurrentLevel())
	{
	case 1:
		if (GameManager->GetIceCrystals() < UPGRADE1_COST) break;

		GameManager->SubstractIceCrystals(UPGRADE1_COST);
		CurrentBuilding->Upgrade();
		break;
	case 2:
		if (GameManager->GetIceCrystals() < UPGRADE2_COST) break;

		GameManager->SubstractIceCrystals(UPGRADE2_COST);

		CurrentBuilding->Upgrade();
		break;
	case 3: 
	default:
		break;
	}
	
}

void UTowerPopupUI::HandleDestroyButtonClicked()
{
	CurrentBuilding->Destroy();
}

auto UTowerPopupUI::SetCurrentBuilding(ATower* a_Building) -> UTowerPopupUI&
{
	CurrentBuilding = a_Building;
	return *this;
}

void UTowerPopupUI::NativeConstruct()
{
	if (GameManager = UGameManager::Instantiate(*this); !GameManager) return;


	GameManager->HandleIceCrystalsChangedDelegate.BindUObject(this, &UTowerPopupUI::HandleIceCrystalsChanged);

	if (UpgradeBtn) UpgradeBtn->OnClicked.AddDynamic(this, &UTowerPopupUI::HandleUpdateButtonClicked);
	if (DestroyBtn) DestroyBtn->OnClicked.AddDynamic(this, &UTowerPopupUI::HandleDestroyButtonClicked);
}

void UTowerPopupUI::NativeDestruct()
{
	if (DestroyBtn) DestroyBtn->OnClicked.RemoveAll(this);
	if (UpgradeBtn) UpgradeBtn->OnClicked.RemoveAll(this);
}
