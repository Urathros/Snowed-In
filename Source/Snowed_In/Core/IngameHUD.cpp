// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/IngameHUD.h"
#include "../UI/HudWidget.h"
#include "Blueprint/UserWidget.h"


const FString AIngameHUD::WIDGET_PATH = FString(TEXT("WidgetBlueprint'/Game/SnowedIn/Blueprints/UI/WBP_HUD'"));

AIngameHUD::AIngameHUD()
{
    HudClass = ConstructorHelpers::FClassFinder<UUserWidget>(*WIDGET_PATH).Class;
}

void AIngameHUD::BeginPlay()
{
    if (HudClass)
    {
        if (HudWidget = CreateWidget<UHudWidget>(GetWorld(), HudClass); HudWidget)
        {
            HudWidget->AddToViewport();
        }
        

    }
}
