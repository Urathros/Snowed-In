// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"


class UButton;
/**
 * 
 */
UCLASS()
class SNOWED_IN_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void HandleGameStart();

	UFUNCTION()
	void HandleOptionsShowing();

	UFUNCTION()
	void HandleCreditsShowing();

	UFUNCTION()
	void HandleGameExit();


	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	static const FString CREDITS_PATH;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonStart", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonStart = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonOptions", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonOptions = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonCredits", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonCredits = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonExit", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonExit = nullptr;



	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "Credits Class", Category = "GUI", AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> CreditsClass = nullptr;

	class SNOWED_IN_API UCreditsWidget* CreditsWidget = nullptr;
};
