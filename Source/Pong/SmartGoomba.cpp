// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartGoomba.h"

#include "Components/BoxComponent.h"

ASmartGoomba::ASmartGoomba()
{
	LeftHoleDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Hole Detector;"));
	RightHoleDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Hole Detector;"));

	LeftHoleDetector->SetupAttachment(RootComponent);
	RightHoleDetector->SetupAttachment(RootComponent);
}

void ASmartGoomba::BeginPlay()
{
	Super::BeginPlay();
	LeftHoleDetector->OnComponentEndOverlap.AddDynamic(this, &ASmartGoomba::LeftEndOverlap);
	RightHoleDetector->OnComponentEndOverlap.AddDynamic(this, &ASmartGoomba::RightEndOverlap);
	if (StartWalkingRight == 1)
	{
		WalkingDirection = 1;
	}

	else if (StartWalkingRight == 0)
	{
		WalkingDirection = -1;
	}
}

void ASmartGoomba::LeftEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Tags.Contains("Floor"))
	{
		WalkingDirection = 1;
	}
}

void ASmartGoomba::RightEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Tags.Contains("Floor"))
	{
		WalkingDirection = -1;
	}
}