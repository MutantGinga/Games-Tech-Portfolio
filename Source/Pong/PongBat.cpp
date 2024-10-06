// Fill out your copyright notice in the Description page of Project Settings.


#include "PongBat.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APongBat::APongBat()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;
	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Bat Hit Box"));
	MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MyCollider->SetBoxExtent(MySprite->Bounds.GetBox().GetSize());
	MyCollider->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APongBat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APongBat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APongBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

