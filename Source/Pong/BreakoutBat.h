// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PongBat.h"
#include "BreakoutBat.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API ABreakoutBat : public APongBat
{
	GENERATED_BODY()

	void MovePlayer(float input);
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	int speed = 1;
	
};
