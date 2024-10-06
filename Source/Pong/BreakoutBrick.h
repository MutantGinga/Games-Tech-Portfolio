// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakoutBrick.generated.h"

UCLASS()
class PONG_API ABreakoutBrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakoutBrick();
	void ChangeHealth(int amount);
	int GetHealth();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperSpriteComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* MyCollider;
	UPROPERTY(EditAnywhere, Category = "Brick Stats")
	int Health = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
