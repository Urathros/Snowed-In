// Copyright Epic Games, Inc. All Rights Reserved.

#include "Snowed_InCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystemInterface.h>
#include <Kismet/GameplayStatics.h>
#include <EnhancedInputSubsystems.h>
#include "InputMappingContext.h"

const FString ASnowed_InCharacter::MAPPING_CTX_PATH = FString(TEXT("InputMappingContext'/Game/SnowedIn/Input/IMC_Pawn'"));
const FString ASnowed_InCharacter::CLICK_IA_PATH = FString(TEXT("InputAction'/Game/SnowedIn/Input/Actions/IA_MouseClick'"));
const FString ASnowed_InCharacter::CANCEL_CLICK_IA_PATH = FString(TEXT("InputAction'/Game/SnowedIn/Input/Actions/IA_MouseCancel'"));
const FString ASnowed_InCharacter::ROTATE_RIGHT_IA_PATH = FString(TEXT("InputAction'/Game/SnowedIn/Input/Actions/IA_RotateRight'"));
const FString ASnowed_InCharacter::ROTATE_LEFT_IA_PATH = FString(TEXT("InputAction'/Game/SnowedIn/Input/Actions/IA_RotateLeft'"));

ASnowed_InCharacter::ASnowed_InCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	//CameraBoom->TargetArmLength = 800.f;
	//CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	//CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	//TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	ClickInputAction = ConstructorHelpers::FObjectFinder<UInputAction>(*CLICK_IA_PATH).Object;
	CancelClickInputAction = ConstructorHelpers::FObjectFinder<UInputAction>(*CANCEL_CLICK_IA_PATH).Object;
	RightRotationInputAction = ConstructorHelpers::FObjectFinder<UInputAction>(*ROTATE_RIGHT_IA_PATH).Object;
	LeftRotationInputAction = ConstructorHelpers::FObjectFinder<UInputAction>(*ROTATE_LEFT_IA_PATH).Object;
	MappingContext = ConstructorHelpers::FObjectFinder<UInputMappingContext>(*MAPPING_CTX_PATH).Object;
}

void ASnowed_InCharacter::HandleMouseClicked(const FInputActionInstance& Instance)
{
	//auto ctx = Instance.GetValue().Get<bool>();
	//UE_LOG(LogTemp, Display, TEXT("Clicked: %s"), ctx ? TEXT("true") : TEXT("false") );
	HandleMouseClickedDelegate.ExecuteIfBound();
}

void ASnowed_InCharacter::HandleMouseCanceled(const FInputActionInstance& Instance)
{
	HandleMouseCanceledDelegate.ExecuteIfBound();
}

void ASnowed_InCharacter::HandleRightRotation(const FInputActionInstance& Instance)
{
	UE_LOG(LogTemp, Display, TEXT("Rotation"));
	HandleRightRotationDelegate.ExecuteIfBound();
}

void ASnowed_InCharacter::HandleLeftRotation(const FInputActionInstance& Instance)
{
	HandleLeftRotationDelegate.ExecuteIfBound();
}

void ASnowed_InCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	GetTopDownCameraComponent()->SetWorldTransform(CameraPosition);
	GetTopDownCameraComponent()->SetFieldOfView(FOV);

}

void ASnowed_InCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ClickInputAction, ETriggerEvent::Triggered, this, &ASnowed_InCharacter::HandleMouseClicked);
		EnhancedInputComponent->BindAction(CancelClickInputAction, ETriggerEvent::Triggered, this, &ASnowed_InCharacter::HandleMouseCanceled);
		EnhancedInputComponent->BindAction(RightRotationInputAction, ETriggerEvent::Started, this, &ASnowed_InCharacter::HandleRightRotation);
		EnhancedInputComponent->BindAction(LeftRotationInputAction, ETriggerEvent::Started, this, &ASnowed_InCharacter::HandleLeftRotation);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASnowed_InCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
