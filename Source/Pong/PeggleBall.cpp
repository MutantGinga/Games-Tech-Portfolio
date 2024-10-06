// Fill out your copyright notice in the Description page of Project Settings.


#include "PeggleBall.h"
#include <Engine.h>

// Sets default values
APeggleBall::APeggleBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;
}

// Called when the game starts or when spawned
void APeggleBall::BeginPlay()
{
	Super::BeginPlay();
	Launcher = Cast<APeggleBallLauncher>(UGameplayStatics::GetActorOfClass(GetWorld(), APeggleBallLauncher::StaticClass()));
}

// Called every frame
void APeggleBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector MyUpdatedLocation = GetActorLocation();
	if (MyUpdatedLocation.Z < -500)
	{
		Launcher->SetReadyToFire(1);
		if (Launcher->GetSpookyActive() == 1)
		{
			MyUpdatedLocation.Z = 300;
			SetActorLocation(MyUpdatedLocation);
			Launcher->SetSpookyActive(0);
		}
		else if (Launcher->GetSpookyActive() == 0)
		{
			DestroyThisObject();
		}
	}
}

void APeggleBall::DestroyThisObject()
{
	Destroy();
}

