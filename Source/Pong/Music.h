// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Music.generated.h"

UCLASS()
class PONG_API AMusic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusic();

	UPROPERTY(EditAnywhere)
	USoundBase* BackgroundMusic;
	UAudioComponent* MusicComponent;

	UPROPERTY(EditAnywhere)
	USoundBase* BallHitSound;
	UAudioComponent* MusicComponentBallHit;
	UFUNCTION()
	void OnAudioFinished();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PlayBallHitSound();

};
