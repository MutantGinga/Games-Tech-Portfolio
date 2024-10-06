// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mario.generated.h"

UENUM()
enum class KnightAnimationState : uint8
{
	AS_WALKING_RIGHT,
	AS_WALKING_LEFT,
	AS_IDLE,
	AS_EMPTY,
	AS_DEAD,
	AS_WON
};

UCLASS()
class PONG_API AMario : public APawn
{
	GENERATED_BODY()

	void MovePlayerHorizontal(float input);
	void Jump();
	void IdentifyAnimStates();
	void ProcessAnimStateMachine();

public:
	// Sets default values for this pawn's properties
	AMario();
	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperFlipbookComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collider")
	class UCapsuleComponent* MyBodyCollider;
	UPROPERTY(VisibleAnywhere, Category = "Camera Setup")
	class USpringArmComponent* MySpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera Setup")
	class UCameraComponent* MyCamera;

	UPROPERTY(EditAnywhere, Category = "Player Properties")
	float JumpForce = 1000;
	UPROPERTY(EditAnywhere, Category = "Player Properties")
	float PlayerAcceleration = 1000;
	UPROPERTY(EditAnywhere, Category = "Player Properties")
	float PlayerMaxSpeed = 32;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_WalkingRight;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Idle;

	UPROPERTY(VisibleAnywhere, Category = "Animations")
	KnightAnimationState CurrentAnimationState;
	UPROPERTY(VisibleAnywhere, Category = "Animations")
	KnightAnimationState OldAnimationState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bIsJumping = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void KillMario();
	void WinGame();

	void BounceMario(float force);

};
