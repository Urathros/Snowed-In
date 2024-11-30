// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/IngameMode.h"
#include "../Core/IngameHUD.h"
#include "../Snowed_InCharacter.h"

AIngameMode::AIngameMode() : Super()
{
	HUDClass = AIngameHUD::StaticClass();
	DefaultPawnClass = ASnowed_InCharacter::StaticClass();
}
