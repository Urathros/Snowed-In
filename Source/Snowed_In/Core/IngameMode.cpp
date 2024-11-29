// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/IngameMode.h"
#include "../Core/IngameHUD.h"

AIngameMode::AIngameMode() : Super()
{
	HUDClass = AIngameHUD::StaticClass();
}
