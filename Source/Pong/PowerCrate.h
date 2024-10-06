// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Crate.h"
#include "PowerCrate.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APowerCrate : public ACrate
{
	GENERATED_BODY()

public:
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	UPROPERTY(EditAnywhere, Category = "Powerups");
	TSubclassOf<AActor> CoinBPClass;
	FTransform SpawnTransform;
};
