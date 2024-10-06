// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <PaperSpriteComponent.h>
#include "ShellItem.generated.h"

UCLASS()
class PONG_API AShellItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShellItem();

	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperSpriteComponent* MySprite;

	UPROPERTY(VisibleAnywhere, Category = "Collider")
	class UCapsuleComponent* MyBodyCollider;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* LeftTrigger;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* RightTrigger;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* HeadTrigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool isMoving;
	FVector direction;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float speed;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float BounceForce;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float ShellMaxSpeed;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float impulseStrength;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float ShellHorizontalAcceleration = 1000.0f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnLeftOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnRightOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherCmp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
