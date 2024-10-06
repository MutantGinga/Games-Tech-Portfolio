// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SawBlade.generated.h"

UCLASS()
class PONG_API ASawBlade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASawBlade();

	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperFlipbookComponent* MySprite;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* KillBox;

	UPROPERTY(EditAnywhere, Category = "Stats")
	FVector StartingVector;
	UPROPERTY(EditAnywhere, Category = "Stats")
	FVector NewVector;
	FVector Change;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int MovementDirection = 1;
	int SawSpeed = 100;
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
