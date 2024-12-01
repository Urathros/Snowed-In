// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/OptionsUserWidget.h"
#include <Components/Button.h>
#include "GameFramework/GameUserSettings.h"

const float UOptionsUserWidget::LOW_RESOLUTION = 50.0f;
const float UOptionsUserWidget::MEDIUM_RESOLUTION = 71.0f;
const float UOptionsUserWidget::HIGH_RESOLUTION = 87.0f;
const float UOptionsUserWidget::EPIC_RESOLUTION = 100.0f;
const int32 UOptionsUserWidget::LOW_QUALITY = 1;
const int32 UOptionsUserWidget::MEDIUM_QUALITY = 2;
const int32 UOptionsUserWidget::HIGH_QUALITY = 3;
const int32 UOptionsUserWidget::EPIC_QUALITY = 4;

UOptionsUserWidget::UOptionsUserWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer) {}

void UOptionsUserWidget::HandleButtonGraphicQualityLowClicked()
{
	if (!Settings) return;

	if (ButtonGraphicQualityLow) ButtonGraphicQualityLow->SetIsEnabled(false);
	if (ButtonGraphicQualityMedium) ButtonGraphicQualityMedium->SetIsEnabled(true);
	if (ButtonGraphicQualityHigh) ButtonGraphicQualityHigh->SetIsEnabled(true);
	if (ButtonGraphicQualityEpic) ButtonGraphicQualityEpic->SetIsEnabled(true);
	if (ButtonGraphicQualityCinematic) ButtonGraphicQualityCinematic->SetIsEnabled(true);

	Settings->ScalabilityQuality.ResolutionQuality = LOW_RESOLUTION;
	Settings->ScalabilityQuality.ViewDistanceQuality = LOW_QUALITY;
	Settings->ScalabilityQuality.AntiAliasingQuality = LOW_QUALITY;
	Settings->ScalabilityQuality.PostProcessQuality = LOW_QUALITY;
	Settings->ScalabilityQuality.ShadowQuality = LOW_QUALITY;
	Settings->ScalabilityQuality.TextureQuality = LOW_QUALITY;
	Settings->ScalabilityQuality.EffectsQuality = LOW_QUALITY;
	Settings->ScalabilityQuality.FoliageQuality = LOW_QUALITY;
	Settings->ScalabilityQuality.ShadingQuality = LOW_QUALITY;
}

void UOptionsUserWidget::HandleButtonGraphicQualityMediumClicked()
{
	if (!Settings) return;

	if (ButtonGraphicQualityLow) ButtonGraphicQualityLow->SetIsEnabled(true);
	if (ButtonGraphicQualityMedium) ButtonGraphicQualityMedium->SetIsEnabled(false);
	if (ButtonGraphicQualityHigh) ButtonGraphicQualityHigh->SetIsEnabled(true);
	if (ButtonGraphicQualityEpic) ButtonGraphicQualityEpic->SetIsEnabled(true);
	if (ButtonGraphicQualityCinematic) ButtonGraphicQualityCinematic->SetIsEnabled(true);

	Settings->ScalabilityQuality.ResolutionQuality = MEDIUM_RESOLUTION;
	Settings->ScalabilityQuality.ViewDistanceQuality = MEDIUM_QUALITY;
	Settings->ScalabilityQuality.AntiAliasingQuality = MEDIUM_QUALITY;
	Settings->ScalabilityQuality.PostProcessQuality = MEDIUM_QUALITY;
	Settings->ScalabilityQuality.ShadowQuality = MEDIUM_QUALITY;
	Settings->ScalabilityQuality.TextureQuality = MEDIUM_QUALITY;
	Settings->ScalabilityQuality.EffectsQuality = MEDIUM_QUALITY;
	Settings->ScalabilityQuality.FoliageQuality = MEDIUM_QUALITY;
	Settings->ScalabilityQuality.ShadingQuality = MEDIUM_QUALITY;
}

void UOptionsUserWidget::HandleButtonGraphicQualityHighClicked()
{
	if (!Settings) return;

	if (ButtonGraphicQualityLow) ButtonGraphicQualityLow->SetIsEnabled(true);
	if (ButtonGraphicQualityMedium) ButtonGraphicQualityMedium->SetIsEnabled(true);
	if (ButtonGraphicQualityHigh) ButtonGraphicQualityHigh->SetIsEnabled(false);
	if (ButtonGraphicQualityEpic) ButtonGraphicQualityEpic->SetIsEnabled(true);
	if (ButtonGraphicQualityCinematic) ButtonGraphicQualityCinematic->SetIsEnabled(true);

	Settings->ScalabilityQuality.ResolutionQuality = HIGH_RESOLUTION;
	Settings->ScalabilityQuality.ViewDistanceQuality = HIGH_QUALITY;
	Settings->ScalabilityQuality.AntiAliasingQuality = HIGH_QUALITY;
	Settings->ScalabilityQuality.PostProcessQuality = HIGH_QUALITY;
	Settings->ScalabilityQuality.ShadowQuality = HIGH_QUALITY;
	Settings->ScalabilityQuality.TextureQuality = HIGH_QUALITY;
	Settings->ScalabilityQuality.EffectsQuality = HIGH_QUALITY;
	Settings->ScalabilityQuality.FoliageQuality = HIGH_QUALITY;
	Settings->ScalabilityQuality.ShadingQuality = HIGH_QUALITY;
}

void UOptionsUserWidget::HandleButtonGraphicQualityEpicClicked()
{
	if (!Settings) return;

	if (ButtonGraphicQualityLow) ButtonGraphicQualityLow->SetIsEnabled(true);
	if (ButtonGraphicQualityMedium) ButtonGraphicQualityMedium->SetIsEnabled(true);
	if (ButtonGraphicQualityHigh) ButtonGraphicQualityHigh->SetIsEnabled(true);
	if (ButtonGraphicQualityEpic) ButtonGraphicQualityEpic->SetIsEnabled(false);
	if (ButtonGraphicQualityCinematic) ButtonGraphicQualityCinematic->SetIsEnabled(true);

	Settings->ScalabilityQuality.ResolutionQuality = EPIC_RESOLUTION;
	Settings->ScalabilityQuality.ViewDistanceQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.AntiAliasingQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.PostProcessQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.ShadowQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.TextureQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.EffectsQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.FoliageQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.ShadingQuality = EPIC_QUALITY;
}

void UOptionsUserWidget::HandleButtonGraphicQualityCinematicClicked()
{
	if (!Settings) return;

	if (ButtonGraphicQualityLow) ButtonGraphicQualityLow->SetIsEnabled(true);
	if (ButtonGraphicQualityMedium) ButtonGraphicQualityMedium->SetIsEnabled(true);
	if (ButtonGraphicQualityHigh) ButtonGraphicQualityHigh->SetIsEnabled(true);
	if (ButtonGraphicQualityEpic) ButtonGraphicQualityEpic->SetIsEnabled(true);
	if (ButtonGraphicQualityCinematic) ButtonGraphicQualityCinematic->SetIsEnabled(false);

	Settings->ScalabilityQuality.ResolutionQuality = EPIC_RESOLUTION;
	Settings->ScalabilityQuality.ViewDistanceQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.AntiAliasingQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.PostProcessQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.ShadowQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.TextureQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.EffectsQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.FoliageQuality = EPIC_QUALITY;
	Settings->ScalabilityQuality.ShadingQuality = EPIC_QUALITY;
}


void UOptionsUserWidget::HandleBackButtonClicked()
{
	RemoveFromParent();
}

void UOptionsUserWidget::NativeConstruct()
{

	if (GEngine && GEngine->GetGameUserSettings() != nullptr)
	{
		Settings = GEngine->GetGameUserSettings();
	}

	if (ButtonGraphicQualityLow) ButtonGraphicQualityLow->OnClicked.AddDynamic(this, &UOptionsUserWidget::HandleButtonGraphicQualityLowClicked);
	if (ButtonGraphicQualityMedium) ButtonGraphicQualityMedium->OnClicked.AddDynamic(this, &UOptionsUserWidget::HandleButtonGraphicQualityMediumClicked);
	if (ButtonGraphicQualityHigh) ButtonGraphicQualityHigh->OnClicked.AddDynamic(this, &UOptionsUserWidget::HandleButtonGraphicQualityHighClicked);
	if (ButtonGraphicQualityEpic) ButtonGraphicQualityEpic->OnClicked.AddDynamic(this, &UOptionsUserWidget::HandleButtonGraphicQualityEpicClicked);
	if (ButtonGraphicQualityCinematic) ButtonGraphicQualityCinematic->OnClicked.AddDynamic(this, &UOptionsUserWidget::HandleButtonGraphicQualityCinematicClicked);


	if (ButtonBack) ButtonBack->OnClicked.AddDynamic(this, &UOptionsUserWidget::HandleBackButtonClicked);
}

void UOptionsUserWidget::NativeDestruct()
{
}
