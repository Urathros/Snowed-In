// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IngameHUD.generated.h"

/**
 *  
 */
UCLASS()
class SNOWED_IN_API AIngameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AIngameHUD();

	virtual void BeginPlay() override;

private:
	static const FString WIDGET_PATH;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "Hud Class", Category = "GUI", AllowPrivateAccess = "true") )
		TSubclassOf<class UUserWidget> HudClass = nullptr;

	class SNOWED_IN_API UHudWidget* HudWidget = nullptr;
};