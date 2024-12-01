// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/MainMenuGameModeBase.h"
#include "../Core/MainMenuHUD.h"

AMainMenuGameModeBase::AMainMenuGameModeBase()
{
	HUDClass = AMainMenuHUD::StaticClass();
}
