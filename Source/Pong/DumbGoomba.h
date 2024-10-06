// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Goomba.h"
#include "DumbGoomba.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API ADumbGoomba : public AGoomba
{
	GENERATED_BODY()

protected:

	UFUNCTION()
	void BeginPlay();
	void Tick(float DeltaTime);

public:
	UPROPERTY(EditAnywhere, Category = "Stats")
	float EnemyHorizontalAcceleration = 1000.0f;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float EnemyMaxSpeed = 500.0f;

};
