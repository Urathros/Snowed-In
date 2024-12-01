// Fill out your copyright notice in the Description page of Project Settings.


#include "../Environment/CalendarSystem.h"
#include "Engine/DirectionalLight.h"
#include "Misc/OutputDeviceNull.h"
#include "TimerManager.h"
#include "../Core/GameManager.h"

// Sets default values
ACalendarSystem::ACalendarSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

auto ACalendarSystem::ForwardTime(void) -> ACalendarSystem&
{
	GetWorld()->GetTimerManager().SetTimer(CalendarHandle, this, &ACalendarSystem::HandleTime, 0.05f, true);
	StartTime = LightSource->GetActorRotation().Euler().Y;
	return *this;
}

void ACalendarSystem::HandleTime()
{
	if (LightSource)
	{
		LightSource->AddActorLocalRotation(FRotator((DeltaSeconds * TurnRate), 0.0, 0.0));
	}

	if (Sun)
	{
		FOutputDeviceNull ar;
		Sun->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, nullptr, true);
	}

	if ((LightSource->GetActorRotation().Euler().Y >= -10.0f && LightSource->GetActorRotation().Euler().Y >= -170) && !bNight)
	{
		GetWorld()->GetTimerManager().ClearTimer(CalendarHandle);
		bNight = true;
	}


	if ((LightSource->GetActorRotation().Euler().Y >= 300 && LightSource->GetActorRotation().Euler().Y >= -60) && bNight)
	{
		GetWorld()->GetTimerManager().ClearTimer(CalendarHandle);
		bNight = false;
	}
}

// Called when the game starts or when spawned
void ACalendarSystem::BeginPlay()
{
	Super::BeginPlay();
	if (GameManager = UGameManager::Instantiate(*this); !GameManager) return;
	GameManager->SetCalendarSystem(this);
}

// Called every frame
void ACalendarSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeltaSeconds = DeltaTime;
}

