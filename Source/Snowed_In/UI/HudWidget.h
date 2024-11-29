// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget.generated.h"


class UImage;
class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class SNOWED_IN_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ImageIceCrystals", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UImage> ImageIceCrystals = nullptr;

		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "TextBlockIceCrystals", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UTextBlock> TextBlockIceCrystals = nullptr;

		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "TextBlockNameTier1", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UTextBlock> TextBlockNameTier1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ImageTier1", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UImage> ImageTier1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonBuyTier1", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UButton> ButtonBuyTier1 = nullptr;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "TextBlockBuyTier1", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UTextBlock> TextBlockBuyTier1 = nullptr;


		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "TextBlockNameTier2", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UTextBlock> TextBlockNameTier2 = nullptr;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ImageTier2", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UImage> ImageTier2 = nullptr;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonBuyTier2", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UButton> ButtonBuyTier2 = nullptr;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "TextBlockBuyTier2", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UTextBlock> TextBlockBuyTier2 = nullptr;


		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "TextBlockNameTier3", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UTextBlock> TextBlockNameTier3 = nullptr;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ImageTier3", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UImage> ImageTier3 = nullptr;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonBuyTier3", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UButton> ButtonBuyTier3 = nullptr;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "TextBlockBuyTier3", BindWidget, AllowPrivateAccess = "true"))
		TObjectPtr<UTextBlock> TextBlockBuyTier3 = nullptr;
};
