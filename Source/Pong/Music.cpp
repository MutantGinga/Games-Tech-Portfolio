// Fill out your copyright notice in the Description page of Project Settings.

#include "Music.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include <Engine.h>

// Sets default values
AMusic::AMusic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	MusicComponent->SetupAttachment(RootComponent);

	MusicComponent->OnAudioFinished.AddDynamic(this, &AMusic::OnAudioFinished);
}

void AMusic::OnAudioFinished()
{
	MusicComponent->Play();
}

// Called when the game starts or when spawned
void AMusic::BeginPlay()
{
	Super::BeginPlay();
	if (MusicComponent)
	{
		MusicComponent->SetSound(BackgroundMusic);
		MusicComponent->Play();
	}
}

// Called every frame
void AMusic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMusic::PlayBallHitSound()
{
	MusicComponentBallHit = UGameplayStatics::SpawnSound2D(this, BallHitSound);
	if (MusicComponentBallHit)
	{
		MusicComponentBallHit->Play();
	}
}

