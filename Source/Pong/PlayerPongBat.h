// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PongBat.h"
#include "PlayerPongBat.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APlayerPongBat : public APongBat
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MovePlayer(float input);
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	int speed = 1;
	
};
