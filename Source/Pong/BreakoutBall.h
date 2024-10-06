// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include "CoreMinimal.h"
#include "GameLogic.h"
#include "Music.h"
#include "GameFramework/Actor.h"
#include "BreakoutBall.generated.h"

UCLASS()
class PONG_API ABreakoutBall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABreakoutBall();
	AGameLogic* GameLogicScoreboard;
	AMusic* SoundPlayer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Sprites");
	class UPaperSpriteComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* MyCollider;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "Ball Stats")
	int ballSpeed = 300;

private:
	FVector MyVelocity;
	float HalfPlayFieldHeight;
	float HalfPlayFieldWidth;
	float MyDeltaTime;
	int BallHalfWidth;

};
