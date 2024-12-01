// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/TowerPopupUI.h"
#include <Components/Button.h>
#include <../Buildings/Tower.h>

UTowerPopupUI::UTowerPopupUI(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer) {}

void UTowerPopupUI::HandleUpdateButtonClicked()
{
	CurrentBuilding->Upgrade();
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
	if (UpgradeBtn) UpgradeBtn->OnClicked.AddDynamic(this, &UTowerPopupUI::HandleUpdateButtonClicked);
	if (DestroyBtn) DestroyBtn->OnClicked.AddDynamic(this, &UTowerPopupUI::HandleDestroyButtonClicked);
}

void UTowerPopupUI::NativeDestruct()
{
}
