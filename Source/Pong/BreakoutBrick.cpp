// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutBrick.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABreakoutBrick::ABreakoutBrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;
	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Bat Hit Box"));
	MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MyCollider->SetBoxExtent(MySprite->Bounds.GetBox().GetSize());
	MyCollider->SetupAttachment(RootComponent);
}

void ABreakoutBrick::ChangeHealth(int amount)
{
	Health -= amount;
}

int ABreakoutBrick::GetHealth()
{
	return Health;
}

// Called when the game starts or when spawned
void ABreakoutBrick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakoutBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

