// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class SNOWED_IN_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPauseWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void HandleGameResume();

	UFUNCTION()
	void HandleOptionsShowing();

	UFUNCTION()
	void HandleCreditsShowing();

	UFUNCTION()
	void HandleMainMenuShowing();

	UFUNCTION()
	void HandleGameExit();


	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	static const FString MENU_LEVEL_NAME;
	static const FString CREDITS_PATH;
	static const FString OPTIONS_PATH;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonResume", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonResume = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonOptions", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonOptions = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonCredits", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonCredits = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonMenu", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonMenu = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonExit", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonExit = nullptr;



	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "Credits Class", Category = "GUI", AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> CreditsClass = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "Options Class", Category = "GUI", AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> OptionsClass = nullptr;

	class SNOWED_IN_API UCreditsWidget* CreditsWidget = nullptr;
	class SNOWED_IN_API UOptionsUserWidget* OptionsWidget = nullptr;
};
