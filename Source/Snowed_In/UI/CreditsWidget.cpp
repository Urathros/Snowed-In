// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/CreditsWidget.h"
#include <Components/Button.h>

UCreditsWidget::UCreditsWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer) {}

void UCreditsWidget::HandleBackButtonClicked()
{
	RemoveFromParent();
}

void UCreditsWidget::NativeConstruct()
{
	if (ButtonBack) ButtonBack->OnClicked.AddDynamic(this, &UCreditsWidget::HandleBackButtonClicked);
}

void UCreditsWidget::NativeDestruct()
{
}
