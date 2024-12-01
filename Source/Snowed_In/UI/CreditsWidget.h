// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsWidget.generated.h"


class UButton;
/**
 * 
 */
UCLASS()
class SNOWED_IN_API UCreditsWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UCreditsWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void HandleBackButtonClicked();

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ButtonBack", BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ButtonBack = nullptr;
};
