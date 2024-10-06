// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include <PaperSpriteActor.h>
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PeggleBallLauncher.generated.h"

UCLASS()
class PONG_API APeggleBallLauncher : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APeggleBallLauncher();
	UPROPERTY(VisibleAnywhere, Category = "Sprites");
	class UPaperSpriteComponent* MySprite;

	UPROPERTY(EditAnywhere, Category = "Ammo");
	TSubclassOf<AActor> BallBPClass;

	bool GetReadyToFire();
	void SetReadyToFire(bool ready_bool);
	bool GetMultiballActive();
	void SetMultiballActive(bool ready_bool);
	bool GetSpookyActive();
	void SetSpookyActive(bool ready_bool);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	UPROPERTY(EditAnywhere, Category = "Launcher Stats")
	int ShotPower = 50000;
	UPROPERTY(EditAnywhere, Category = "Launcher Stats")
	bool ReadyToFire = 1;
	bool MultiballActive = 0;
	bool SpookyActive = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MovePlayer(float input);

	void Fire();

};
