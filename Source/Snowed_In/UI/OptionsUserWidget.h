// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsUserWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SNOWED_IN_API UOptionsUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UOptionsUserWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void HandleButtonGraphicQualityLowClicked();

	UFUNCTION()
	void HandleButtonGraphicQualityMediumClicked();

	UFUNCTION()
	void HandleButtonGraphicQualityHighClicked();

	UFUNCTION()
	void HandleButtonGraphicQualityEpicClicked();

	UFUNCTION()
	void HandleButtonGraphicQualityCinematicClicked();

	UFUNCTION()
	void HandleBackButtonClicked();

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	static const float LOW_RESOLUTION;
	static const float MEDIUM_RESOLUTION;
	static const float HIGH_RESOLUTION;
	static const float EPIC_RESOLUTION;
	static const int32 LOW_QUALITY;
	static const int32 MEDIUM_QUALITY;
	static const int32 HIGH_QUALITY;
	static const int32 EPIC_QUALITY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonGraphicQualityLow", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonGraphicQualityLow = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonGraphicQualityMedium", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonGraphicQualityMedium = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonGraphicQualityHigh", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonGraphicQualityHigh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonGraphicQualityEpic", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonGraphicQualityEpic = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonGraphicQualityCinematic", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonGraphicQualityCinematic = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonBack", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonBack = nullptr;


	UGameUserSettings* Settings = nullptr;
};
