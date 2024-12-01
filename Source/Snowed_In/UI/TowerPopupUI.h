// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerPopupUI.generated.h"

class UButton; 
class ATower;

/**
 * 
 */
UCLASS()
class SNOWED_IN_API UTowerPopupUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UTowerPopupUI(const FObjectInitializer& ObjectInitializer);


	UFUNCTION()
	void HandleIceCrystalsChanged();

	UFUNCTION()
	void HandleUpdateButtonClicked();

	UFUNCTION()
	void HandleDestroyButtonClicked();

	auto SetCurrentBuilding(ATower* a_Building) -> UTowerPopupUI&;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	static const uint32 UPGRADE1_COST;
	static const uint32 UPGRADE2_COST;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Game Manager", AllowPrivateAccess = "true"))
	class UGameManager* GameManager = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* UpgradeBtn = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* DestroyBtn = nullptr;


	class ATower* CurrentBuilding = nullptr;
};
