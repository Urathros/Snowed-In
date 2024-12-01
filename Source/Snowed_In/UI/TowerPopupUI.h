// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerPopupUI.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class SNOWED_IN_API UTowerPopupUI : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UButton* UpgradeBtn = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* DestroyBtn = nullptr;
};
