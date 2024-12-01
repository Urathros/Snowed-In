// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/MainMenuWidget.h"
#include <Components/Button.h>
#include "Kismet/GameplayStatics.h"
#include "CreditsWidget.h"

const FString UMainMenuWidget::CREDITS_PATH = FString(TEXT("WidgetBlueprint'/Game/SnowedIn/Blueprints/UI/WBP_Credits'"));


UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer) 
{
	CreditsClass = ConstructorHelpers::FClassFinder<UUserWidget>(*CREDITS_PATH).Class;
}

void UMainMenuWidget::HandleGameStart()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Game");
}

void UMainMenuWidget::HandleOptionsShowing()
{
}

void UMainMenuWidget::HandleCreditsShowing()
{
	if (CreditsWidget)
	{
		CreditsWidget->AddToViewport();
	}
}

void UMainMenuWidget::HandleGameExit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), 0, EQuitPreference::Quit, false);
}

void UMainMenuWidget::NativeConstruct()
{
	if (CreditsClass) CreditsWidget = CreateWidget<UCreditsWidget>(GetWorld(), CreditsClass);

	if (ButtonStart) ButtonStart->OnClicked.AddDynamic(this, &UMainMenuWidget::HandleGameStart);
	if (ButtonOptions) ButtonOptions->OnClicked.AddDynamic(this, &UMainMenuWidget::HandleOptionsShowing);
	if (ButtonCredits) ButtonCredits->OnClicked.AddDynamic(this, &UMainMenuWidget::HandleCreditsShowing);
	if (ButtonExit) ButtonExit->OnClicked.AddDynamic(this, &UMainMenuWidget::HandleGameExit);
}

void UMainMenuWidget::NativeDestruct()
{
}
