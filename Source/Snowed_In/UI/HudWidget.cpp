// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/HudWidget.h"
#include "../Core/GameManager.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>

const FString UHudWidget::TIER1_TEXT = FString(TEXT("Tier 1"));
const FString UHudWidget::TIER2_TEXT = FString(TEXT("Tier 2"));
const FString UHudWidget::TIER3_TEXT = FString(TEXT("Tier 3"));
const uint32 UHudWidget::TIER1_COST = 50;
const uint32 UHudWidget::TIER2_COST = 500;
const uint32 UHudWidget::TIER3_COST = 5000;

UHudWidget::UHudWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer) {}

void UHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameManager = UGameManager::Instantiate(*this);

	if(TextBlockIceCrystals) TextBlockIceCrystals->SetText(FText::FromString( FString::FromInt(GameManager->GetIceCrystals())));
	if (TextBlockNameTier1) TextBlockNameTier1->SetText(FText::FromString(TIER1_TEXT));
	if (TextBlockNameTier2) TextBlockNameTier2->SetText(FText::FromString(TIER2_TEXT));
	if(TextBlockNameTier3) TextBlockNameTier3->SetText(FText::FromString(TIER3_TEXT));
	if (TextBlockBuyTier1) TextBlockBuyTier1->SetText(FText::FromString(FString::FromInt(TIER1_COST)));
	if (TextBlockBuyTier2) TextBlockBuyTier2->SetText(FText::FromString(FString::FromInt(TIER2_COST)));
	if(TextBlockBuyTier3) TextBlockBuyTier3->SetText(FText::FromString(FString::FromInt(TIER3_COST)));
}