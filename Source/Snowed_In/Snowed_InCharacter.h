// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Snowed_InCharacter.generated.h"


DECLARE_DELEGATE(FHandleMouseClickedSignature);
DECLARE_DELEGATE(FHandleMouseCanceledSignature);
DECLARE_DELEGATE(FHandleRightRotationSignature);
DECLARE_DELEGATE(FHandleLeftRotationSignature);

UCLASS(Blueprintable)
class ASnowed_InCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASnowed_InCharacter();

	void HandleMouseClicked(const struct FInputActionInstance& Instance);
	void HandleMouseCanceled(const struct FInputActionInstance& Instance);
	void HandleRightRotation(const struct FInputActionInstance& Instance);
	void HandleLeftRotation(const struct FInputActionInstance& Instance);
	void HandlePause(const struct FInputActionInstance& Instance);

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:

	static const FString MAPPING_CTX_PATH;
	static const FString CLICK_IA_PATH;
	static const FString CANCEL_CLICK_IA_PATH;
	static const FString ROTATE_RIGHT_IA_PATH;
	static const FString ROTATE_LEFT_IA_PATH;
	static const FString PAUSE_IA_PATH;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "HUD", AllowPrivateAccess = "true"))
	class AIngameHUD* HUD = nullptr;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true", MakeEditWidget = true))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true", MakeEditWidget = true))
	FTransform CameraPosition = FTransform(FRotator(-45.0f, 0.0f, 0.0f), FVector(-750.0f, 1750.0f, 2000.0f), FVector(1.0f, 1.0f, 1.0f));

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float FOV = 40.0f;

	/** Camera boom positioning the camera above the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* ClickInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* CancelClickInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* RightRotationInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LeftRotationInputAction;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PauseInputAction;

public:
	FHandleMouseClickedSignature HandleMouseClickedDelegate = nullptr;
	FHandleMouseCanceledSignature HandleMouseCanceledDelegate = nullptr;
	FHandleRightRotationSignature HandleRightRotationDelegate = nullptr;
	FHandleLeftRotationSignature HandleLeftRotationDelegate = nullptr;
};

