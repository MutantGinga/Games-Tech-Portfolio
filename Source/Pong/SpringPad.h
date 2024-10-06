// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mario.h"
#include "GameFramework/Actor.h"
#include "SpringPad.generated.h"

UENUM()
enum class SpringAnimationState : uint8
{
	AS_READY,
	AS_SPRUNG
};

UCLASS()
class PONG_API ASpringPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringPad();

	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperFlipbookComponent* MySprite;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* SpringBoard;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* SpringBody;


	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Ready;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Sprung;

	UPROPERTY(VisibleAnywhere, Category = "Animations")
	SpringAnimationState CurrentAnimationState;
	UPROPERTY(VisibleAnywhere, Category = "Animations")
	SpringAnimationState OldAnimationState;

	bool SpringSprung = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void IdentifyAnimStates();
	void ProcessAnimStateMachine();

	void ResetSpring();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Stats")
	int BounceForce = 1000;

private:
	FTimerHandle SpringTimer;
};
