// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/MainMenuWidget.h"
#include <Components/Button.h>
#include "Kismet/GameplayStatics.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer) {}

void UMainMenuWidget::HandleGameStart()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Game");
}

void UMainMenuWidget::HandleOptionsShowing()
{
}

void UMainMenuWidget::HandleCreditsShowing()
{
}

void UMainMenuWidget::HandleGameExit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), 0, EQuitPreference::Quit, false);
}

void UMainMenuWidget::NativeConstruct()
{
	if (ButtonStart) ButtonStart->OnClicked.AddDynamic(this, &UMainMenuWidget::HandleGameStart);
	if (ButtonOptions) ButtonOptions->OnClicked.AddDynamic(this, &UMainMenuWidget::HandleOptionsShowing);
	if (ButtonCredits) ButtonCredits->OnClicked.AddDynamic(this, &UMainMenuWidget::HandleCreditsShowing);
	if (ButtonExit) ButtonExit->OnClicked.AddDynamic(this, &UMainMenuWidget::HandleGameExit);
}

void UMainMenuWidget::NativeDestruct()
{
}
