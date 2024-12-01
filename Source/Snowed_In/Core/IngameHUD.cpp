// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/IngameHUD.h"
#include "../UI/HudWidget.h"
#include "../UI/PauseWidget.h"
#include "Blueprint/UserWidget.h"
#include "../Core/GameManager.h"


const FString AIngameHUD::WIDGET_PATH = FString(TEXT("WidgetBlueprint'/Game/SnowedIn/Blueprints/UI/WBP_HUD'"));
const FString AIngameHUD::PAUSE_PATH = FString(TEXT("WidgetBlueprint'/Game/SnowedIn/Blueprints/UI/WBP_Pause'"));

AIngameHUD::AIngameHUD()
{
    HudClass = ConstructorHelpers::FClassFinder<UUserWidget>(*WIDGET_PATH).Class;
    PauseClass = ConstructorHelpers::FClassFinder<UUserWidget>(*PAUSE_PATH).Class;
}

void AIngameHUD::HandleHudWidgetCreation()
{
    if (HudWidget) HudWidget->AddToViewport();
}

auto AIngameHUD::GetPause(void) const -> const bool
{
    return bPause;
}

auto AIngameHUD::SetPause(const bool& a_bPause) -> AIngameHUD&
{
    bPause = a_bPause;
    bPause ? PauseWidget->AddToViewport() : PauseWidget->RemoveFromParent();
    return *this;
}

void AIngameHUD::BeginPlay()
{
    if (GameManager = UGameManager::Instantiate(*this); !GameManager) return;
    if (PlayerController = GetWorld()->GetFirstPlayerController(); !PlayerController) return;

    PlayerController->bShowMouseCursor = true;
    PlayerController->bEnableClickEvents = true;
    PlayerController->bEnableMouseOverEvents = true;

    //GameManager->HandleHUDCreationDelegate.BindUObject(this, &AIngameHUD::HandleHudWidgetCreation);
    GameManager->HandleWaveClearedDelegate.BindUObject(this, &AIngameHUD::HandleHudWidgetCreation);

    if (HudClass)
    {
        if (HudWidget = CreateWidget<UHudWidget>(GetWorld(), HudClass); HudWidget)
        {
            HudWidget->AddToViewport();
        }
    }


    if (PauseClass)
    {
        if (PauseWidget = CreateWidget<UPauseWidget>(GetWorld(), PauseClass); PauseWidget)
        {
            //PauseWidget->AddToViewport();
        }
    }
}
