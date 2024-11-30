// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CalendarSystem.generated.h"

UCLASS()
class SNOWED_IN_API ACalendarSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACalendarSystem();

	auto ForwardTime(void) -> ACalendarSystem&;
private:
	UFUNCTION()
	void HandleTime();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Game Manager", AllowPrivateAccess = "true"))
	class UGameManager* GameManager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Night", Category = "Sky", AllowPrivateAccess = "true"))
	bool bNight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Start Time", Category = "Sky", AllowPrivateAccess = "true"))
	float StartTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Delta Seconds", Category = "Sky", AllowPrivateAccess = "true"))
	float DeltaSeconds = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Sun", Category = "Sky", AllowPrivateAccess = "true"))
		AActor* Sun = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Light Source", Category = "Sky", AllowPrivateAccess = "true"))
		class ADirectionalLight* LightSource = nullptr;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Turn Rate", Category = "Sky", AllowPrivateAccess = "true"))
		float TurnRate = 500.0f;

		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Calendar Handle", Category = "Sky", AllowPrivateAccess = "true"))
		FTimerHandle CalendarHandle;


};
