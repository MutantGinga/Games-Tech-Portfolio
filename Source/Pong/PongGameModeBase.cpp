// Copyright Epic Games, Inc. All Rights Reserved.


#include "PongGameModeBase.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void APongGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->ConsoleCommand("t.MaxFPS 60", true);
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("r.VSync 1", true);
}
