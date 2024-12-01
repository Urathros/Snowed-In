// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/MainMenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "../UI/MainMenuWidget.h"

const FString AMainMenuHUD::WIDGET_PATH = FString(TEXT("WidgetBlueprint'/Game/SnowedIn/Blueprints/UI/WBP_MainMenu'"));

AMainMenuHUD::AMainMenuHUD()
{
	MenuClass = ConstructorHelpers::FClassFinder<UUserWidget>(*WIDGET_PATH).Class;
}

void AMainMenuHUD::BeginPlay()
{
    if (MenuClass)
    {
        if (MenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MenuClass); MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }
}
