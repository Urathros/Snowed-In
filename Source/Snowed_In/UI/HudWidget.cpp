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

	UE_LOG(LogTemp, Display, TEXT("Button Buy Tier 1 Clicked!"));

	if (PlayerController) PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	UE_LOG(LogTemp, Display, TEXT("x: %s y: %s z: %s"), *FString::FromInt(MouseLocation.X), *FString::FromInt(MouseLocation.Y), *FString::FromInt(MouseLocation.Z));

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	

	CurrentBuilding = GetWorld()->SpawnActor<ATower>(FVector(MouseLocation.X - 150.0f, MouseLocation.Y - 225.0f, 0.0f), FRotator::MakeFromEuler(MouseDirection), SpawnInfo);

	float x = 0.0f, y = 0.0f;

	if (!PlayerController->GetMousePosition(x, y)) return;
	Dir.X = y  * 0.25f;
	Dir.Y = x  * 0.25f;

	CurrentBuilding->SetActorLocation(CurrentBuilding->GetActorLocation() + Dir);
	LastPos = FVector(x, y, 0.0f);

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
	GetWorld()->GetTimerManager().SetTimer(MoveBuildingHandle, this, &UHudWidget::HandleBuildingMovement, 1.0f, true);
	if (ButtonBuyTier1) ButtonBuyTier1->SetIsEnabled(false);
}

void UHudWidget::HandleButtonBuyTier2Clicked()
{
	UE_LOG(LogTemp, Display, TEXT("Button Buy Tier 2 Clicked!"));
}

void UHudWidget::HandleCancelButtonClicked()
{
	if (GameManager) GameManager->SetInBuildMode(false);
	RemoveFromParent();
}

void UHudWidget::HandleButtonBuyTier3Clicked()
{
	UE_LOG(LogTemp, Display, TEXT("Button Buy Tier 3 Clicked!"));
}

void UHudWidget::HandleMoveableDisabling()
{
	GetWorld()->GetTimerManager().ClearTimer(MoveBuildingHandle);
	if (ButtonBuyTier1) ButtonBuyTier1->SetIsEnabled(true);
	UE_LOG(LogTemp, Display, TEXT("Moveable is false"));
	Character->HandleMouseCanceledDelegate.Unbind();


}

void UHudWidget::HandleBuildingMovement()
{
	//if (PlayerController) PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	//CurrentBuilding->SetActorLocation(CurrentBuilding->GetActorLocation() * MouseDirection /** Speed * GetWorld()->GetDeltaSeconds()*/);
	//CurrentBuilding->SetActorRotation(FRotator::MakeFromEuler(MouseDirection));

	//UE_LOG(LogTemp, Display, TEXT("x: %s y: %s z: %s"), *FString::FromInt(MouseDirection.X), *FString::FromInt(MouseDirection.Y), *FString::FromInt(MouseDirection.Z));
	float x = 0.0f, y = 0.0f;

	if(!PlayerController->GetMousePosition(x, y)) return;
	Dir.X = (y - LastPos.Y) * 0.4f;
	Dir.Y = (x - LastPos.X) * 0.4f;

	if (LastPos.X != 0.0f) Dir.X *= -1.0f;

	//Dir.Normalize();
	UE_LOG(LogTemp, Display, TEXT("x: %s y: %s z: %s"), *FString::FromInt(Dir.Y), *FString::FromInt(Dir.X), *FString::FromInt(Dir.Z));

	CurrentBuilding->SetActorLocation(CurrentBuilding->GetActorLocation() + Dir);
	//CurrentBuilding->SetActorRotation(FRotator::MakeFromEuler(MouseDirection));
	UE_LOG(LogTemp, Display, TEXT("Moving"));
	LastPos = FVector(x, y, 0.0f);
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
