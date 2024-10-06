// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheLessDumbGoomba.h"
#include "SmartGoomba.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API ASmartGoomba : public ATheLessDumbGoomba
{
	GENERATED_BODY()

	void BeginPlay();

	UFUNCTION()
	void LeftEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void RightEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	ASmartGoomba();

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* LeftHoleDetector;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* RightHoleDetector;

	UPROPERTY(EditAnywhere, Category = "Stats")
	bool StartWalkingRight;
	
};
