// Fill out your copyright notice in the Description page of Project Settings.

#include "GameLogic.h"
#include "Blueprint/UserWidget.h"
#include <Misc/OutputDeviceNull.h>
#include <Engine.h>

// Sets default values
AGameLogic::AGameLogic() : playerScore(0), AIScore(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

int AGameLogic::GetScore(int player)
{
	if (player == 1)
	{
		return playerScore;
	}

	else if (player == 2)
	{
		return AIScore;
	}

	return -1;
}

void AGameLogic::SetScore(int player, int updated_score)
{
	if (player == 1)
	{
		playerScore = updated_score;
	}

	else if (player == 2)
	{
		AIScore = updated_score;
	}
}

void AGameLogic::IncrementScore(int player, int increment)
{
	FString command;

	if (player == 1)
	{
		playerScore += increment;
		command = FString::Printf(TEXT("UpdatePlayerScore %d"), playerScore);
	}

	else if (player == 2)
	{
		AIScore += increment;
		command = FString::Printf(TEXT("UpdateAIScore %d"), AIScore);
	}

	if (ScoreUIInstance != nullptr)
	{
		FOutputDeviceNull odn;
		ScoreUIInstance->CallFunctionByNameWithArguments(*command, odn, nullptr, true);
	}
}

void AGameLogic::YouWon()
{

	UGameplayStatics::OpenLevel(this, "L_YouWon", true);
}

void AGameLogic::YouLost()
{
	UGameplayStatics::OpenLevel(this, "L_YouLost", true);
}

// Called when the game starts or when spawned
void AGameLogic::BeginPlay()
{
	Super::BeginPlay();
	
	if (ScoreUIClass != nullptr)
	{
		ScoreUIInstance = CreateWidget<UUserWidget>(GetWorld(), ScoreUIClass);
		if (ScoreUIInstance != nullptr)
		{
			ScoreUIInstance->AddToViewport();
		}
	}
}

// Called every frame
void AGameLogic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

