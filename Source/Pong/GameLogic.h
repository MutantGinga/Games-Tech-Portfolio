// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "GameLogic.generated.h"

UCLASS()
class PONG_API AGameLogic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameLogic();
	UFUNCTION(BlueprintCallable, Category = "Score")
	int GetScore(int player);
	void SetScore(int player, int updated_score);
	void IncrementScore(int player, int score);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> ScoreUIClass;

	UUserWidget* ScoreUIInstance;

	void YouWon();
	void YouLost();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int playerScore = 0;
	int AIScore = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
