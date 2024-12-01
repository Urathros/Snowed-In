// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class SNOWED_IN_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
public:
	AMainMenuHUD();

	virtual void BeginPlay() override;

private:

	static const FString WIDGET_PATH;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "Menu Class", Category = "GUI", AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> MenuClass = nullptr;

	class SNOWED_IN_API UMainMenuWidget* MenuWidget = nullptr;
};
