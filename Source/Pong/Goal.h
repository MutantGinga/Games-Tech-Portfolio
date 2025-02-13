// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UCLASS()
class PONG_API AGoal : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperFlipbookComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* GoalHitbox;
	
public:	
	// Sets default values for this actor's properties
	AGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit);
};
