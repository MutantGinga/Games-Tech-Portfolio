// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmartGoomba.h"
#include "ShellEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API AShellEnemy : public ASmartGoomba
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Powerups");
	TSubclassOf<AActor> ShellBPClass;
	FTransform SpawnTransform;

protected:

	void OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
