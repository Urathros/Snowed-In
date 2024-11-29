// Copyright Epic Games, Inc. All Rights Reserved.

#include "Snowed_InGameMode.h"
#include "Snowed_InPlayerController.h"
#include "Snowed_InCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASnowed_InGameMode::ASnowed_InGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASnowed_InPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}