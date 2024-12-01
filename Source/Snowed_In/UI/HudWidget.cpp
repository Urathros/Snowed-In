// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/HudWidget.h"
#include "../Core/GameManager.h"
#include "../Snowed_InCharacter.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <../Buildings/Tower.h>
#include "TimerManager.h"
#include "Engine/World.h"
#include "../Environment/CalendarSystem.h"

const FString UHudWidget::CANCEL_TEXT = FString(TEXT("Cancel"));
const FString UHudWidget::TIER1_TEXT = FString(TEXT("Tier 1"));
const FString UHudWidget::TIER2_TEXT = FString(TEXT("Tier 2"));
const FString UHudWidget::TIER3_TEXT = FString(TEXT("Tier 3"));
const uint32 UHudWidget::TIER1_COST = 50;
const uint32 UHudWidget::TIER2_COST = 500;
const uint32 UHudWidget::TIER3_COST = 5000;

UHudWidget::UHudWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer) {}

void UHudWidget::HandleIceCrystalsChanged()
{
	if (!GameManager) return;

	const auto&& iceCrystals = GameManager->GetIceCrystals();
	if (TextBlockIceCrystals) TextBlockIceCrystals->SetText(FText::FromString(FString::FromInt(iceCrystals)));
	if (ButtonBuyTier1) ButtonBuyTier1->SetIsEnabled(!(iceCrystals < TIER1_COST));
	if (ButtonBuyTier2) ButtonBuyTier2->SetIsEnabled(!(iceCrystals < TIER2_COST));
	if (ButtonBuyTier3) ButtonBuyTier3->SetIsEnabled(!(iceCrystals < TIER3_COST));
}

void UHudWidget::HandleButtonBuyTier1Clicked()
{
	if (!PlayerController) return;

	UE_LOG(LogTemp, Display, TEXT("Button Buy Tier 1 Clicked!"));

	FHitResult hit = {};
	auto result = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, hit);
	if (!result) return;

	MouseLocation = hit.Location;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentBuilding = GetWorld()->SpawnActor<ATower>(FVector(MouseLocation.X, MouseLocation.Y, MouseLocation.Z), FRotator(0.f), SpawnInfo);

	if (Character)
	{
		Character->HandleMouseClickedDelegate.Unbind();
		Character->HandleMouseClickedDelegate.BindUObject(this, &UHudWidget::HandleMoveableDisabling);
		Character->HandleMouseCanceledDelegate.Unbind();
		Character->HandleMouseCanceledDelegate.BindUObject(this, &UHudWidget::HandleBuildingAbort);
		Character->HandleRightRotationDelegate.Unbind();
		Character->HandleRightRotationDelegate.BindUObject(this, &UHudWidget::HandleRightRotation);
		Character->HandleLeftRotationDelegate.Unbind();
		Character->HandleLeftRotationDelegate.BindUObject(this, &UHudWidget::HandleLeftRotation);
	}

	GetWorld()->GetTimerManager().ClearTimer(MoveBuildingHandle);
	GetWorld()->GetTimerManager().SetTimer(MoveBuildingHandle, this, &UHudWidget::HandleBuildingMovement, 0.05f, true);
	if (ButtonBuyTier1) ButtonBuyTier1->SetIsEnabled(false);
}

void UHudWidget::HandleButtonBuyTier2Clicked()
{
	UE_LOG(LogTemp, Display, TEXT("Button Buy Tier 2 Clicked!"));
}

void UHudWidget::HandleCancelButtonClicked()
{
	if (!GameManager) return;
	GameManager->SetInBuildMode(false);
	if (const auto calendar = GameManager->GetCalendarSystem()) calendar->ForwardTime();
	RemoveFromParent();
}

void UHudWidget::HandleButtonBuyTier3Clicked()
{
	UE_LOG(LogTemp, Display, TEXT("Button Buy Tier 3 Clicked!"));
}

void UHudWidget::HandleMoveableDisabling()
{
	if (!GameManager) return;

	GetWorld()->GetTimerManager().ClearTimer(MoveBuildingHandle);
	GameManager->SubstractIceCrystals(TIER1_COST);
	if (ButtonBuyTier1 && (GameManager->GetIceCrystals() >= TIER1_COST)) ButtonBuyTier1->SetIsEnabled(true);
	Character->HandleMouseCanceledDelegate.Unbind();
	CurrentBuilding->Activate();

}

void UHudWidget::HandleBuildingMovement()
{
	if (!CurrentBuilding) return;

	FHitResult hit = {};
	auto result = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, hit);
	if (result)
	{
		CurrentBuilding->SetActorLocation(GameManager->ConvertPosToGrid(hit.Location));
	}
}

void UHudWidget::HandleBuildingAbort()
{
	if (CurrentBuilding) CurrentBuilding->Destroy();
	if (ButtonBuyTier1) ButtonBuyTier1->SetIsEnabled(true);
}

void UHudWidget::HandleRightRotation()
{
	auto rota = CurrentBuilding->GetActorRotation().Euler();
	rota.Z += 90;
	CurrentBuilding->SetActorRotation(FRotator::MakeFromEuler(rota));
}

void UHudWidget::HandleLeftRotation()
{
	auto rota = CurrentBuilding->GetActorRotation().Euler();
	rota.Z -= 90;
	CurrentBuilding->SetActorRotation(FRotator::MakeFromEuler(rota));
}

void UHudWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (PlayerController = GetWorld()->GetFirstPlayerController(); !PlayerController) return;
	if (Character = PlayerController->GetPawn<ASnowed_InCharacter>(); !Character) return;

	if (GameManager = UGameManager::Instantiate(*this); !GameManager) return;

	GameManager->HandleIceCrystalsChangedDelegate.BindUObject(this, &UHudWidget::HandleIceCrystalsChanged);
	const auto&& iceCrystals = GameManager->GetIceCrystals();
	if(TextBlockIceCrystals) TextBlockIceCrystals->SetText(FText::FromString( FString::FromInt(iceCrystals)));
	if (TextBlockNameTier1) TextBlockNameTier1->SetText(FText::FromString(TIER1_TEXT));
	if (TextBlockNameTier2) TextBlockNameTier2->SetText(FText::FromString(TIER2_TEXT));
	if(TextBlockNameTier3) TextBlockNameTier3->SetText(FText::FromString(TIER3_TEXT));
	if (TextBlockBuyTier1) TextBlockBuyTier1->SetText(FText::FromString(FString::FromInt(TIER1_COST)));
	if (TextBlockBuyTier2) TextBlockBuyTier2->SetText(FText::FromString(FString::FromInt(TIER2_COST)));
	if(TextBlockBuyTier3) TextBlockBuyTier3->SetText(FText::FromString(FString::FromInt(TIER3_COST)));
	if (ButtonBuyTier1)
	{
		ButtonBuyTier1->SetIsEnabled(!(iceCrystals < TIER1_COST));
		ButtonBuyTier1->OnClicked.AddDynamic(this, &UHudWidget::HandleButtonBuyTier1Clicked);
	}
	if (ButtonBuyTier2) 
	{
		ButtonBuyTier2->SetIsEnabled(!(iceCrystals < TIER2_COST));
		ButtonBuyTier2->OnClicked.AddDynamic(this, &UHudWidget::HandleButtonBuyTier2Clicked);
	}
	if (ButtonBuyTier3)
	{
		ButtonBuyTier3->SetIsEnabled(!(iceCrystals < TIER3_COST));
		ButtonBuyTier3->OnClicked.AddDynamic(this, &UHudWidget::HandleButtonBuyTier3Clicked);
	}

	if (ButtonCancel) ButtonCancel->OnClicked.AddDynamic(this, &UHudWidget::HandleCancelButtonClicked);
	if (TextBlockCancel) TextBlockCancel->SetText(FText::FromString(CANCEL_TEXT));

	GameManager->SetIceCrystals(55); //Test
}

void UHudWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (!GameManager) return;
	GameManager->HandleIceCrystalsChangedDelegate.Unbind();
}
