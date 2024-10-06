// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Goomba.generated.h"

UENUM()
enum class SkeletonAnimationState : uint8
{
	AS_WALKING_RIGHT,
	AS_WALKING_LEFT,
	AS_IDLE,
	AS_EMPTY,
	AS_DEAD
};

UCLASS()
class PONG_API AGoomba : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoomba();

	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperFlipbookComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collider")
	class UCapsuleComponent* MyBodyCollider;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* LeftTrigger;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* RightTrigger;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* HeadTrigger;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_WalkingRight;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Idle;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Death;

	UPROPERTY(VisibleAnywhere, Category = "Animations")
	SkeletonAnimationState CurrentAnimationState;
	UPROPERTY(VisibleAnywhere, Category = "Animations")
	SkeletonAnimationState OldAnimationState;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float BounceForce = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void IdentifyAnimStates();

	void ProcessAnimStateMachine();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void KillGoomba();

};
