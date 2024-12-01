// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/PauseWidget.h"
#include <Components/Button.h>
#include "Kismet/GameplayStatics.h"
#include "CreditsWidget.h"
#include "OptionsUserWidget.h"

const FString UPauseWidget::MENU_LEVEL_NAME = FString(TEXT("Menu"));
const FString UPauseWidget::CREDITS_PATH = FString(TEXT("WidgetBlueprint'/Game/SnowedIn/Blueprints/UI/WBP_Credits'"));
const FString UPauseWidget::OPTIONS_PATH = FString(TEXT("WidgetBlueprint'/Game/SnowedIn/Blueprints/UI/WBP_Options'"));

UPauseWidget::UPauseWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	CreditsClass = ConstructorHelpers::FClassFinder<UUserWidget>(*CREDITS_PATH).Class;
	OptionsClass = ConstructorHelpers::FClassFinder<UUserWidget>(*OPTIONS_PATH).Class;
}

void UPauseWidget::HandleGameResume()
{
	RemoveFromParent();
}

void UPauseWidget::HandleOptionsShowing()
{
	if (OptionsWidget) OptionsWidget->AddToViewport();
}

void UPauseWidget::HandleCreditsShowing()
{
	if (CreditsWidget) CreditsWidget->AddToViewport();
}

void UPauseWidget::HandleMainMenuShowing()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*MENU_LEVEL_NAME));
}

void UPauseWidget::HandleGameExit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), 0, EQuitPreference::Quit, false);
}

void UPauseWidget::NativeConstruct()
{
	if (CreditsClass) CreditsWidget = CreateWidget<UCreditsWidget>(GetWorld(), CreditsClass);
	if (OptionsClass) OptionsWidget = CreateWidget<UOptionsUserWidget>(GetWorld(), OptionsClass);

	if (ButtonResume) ButtonResume->OnClicked.AddDynamic(this, &UPauseWidget::HandleGameResume);
	if (ButtonOptions) ButtonOptions->OnClicked.AddDynamic(this, &UPauseWidget::HandleOptionsShowing);
	if (ButtonCredits) ButtonCredits->OnClicked.AddDynamic(this, &UPauseWidget::HandleCreditsShowing);
	if (ButtonMenu) ButtonMenu->OnClicked.AddDynamic(this, &UPauseWidget::HandleMainMenuShowing);
	if (ButtonExit) ButtonExit->OnClicked.AddDynamic(this, &UPauseWidget::HandleGameExit);
}

void UPauseWidget::NativeDestruct()
{
}
