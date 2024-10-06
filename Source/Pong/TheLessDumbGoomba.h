// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DumbGoomba.h"
#include "TheLessDumbGoomba.generated.h"

/**
 *
 */
UCLASS()
class PONG_API ATheLessDumbGoomba : public ADumbGoomba
{
	GENERATED_BODY()

	void Tick(float DeltaTime);

	UFUNCTION()
	void OnLeftOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnRightOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	int WalkingDirection = -1;
	void BeginPlay();
};
