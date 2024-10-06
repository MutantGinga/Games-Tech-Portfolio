// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DumbGoomba.h"
#include "LessDumbGoomba.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API ALessDumbGoomba : public ADumbGoomba
{
	GENERATED_BODY()
	
	void BeginPlay();
	void Tick(float DeltaTime);

	void OnLeftOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnRightOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherCOmp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	int WalkingDirection;
};
