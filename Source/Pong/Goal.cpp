// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal.h"
#include "Mario.h"
#include <PaperFlipbookComponent.h>
#include <Components/BoxComponent.h>

// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Goal Sprite"));
	GoalHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("My Left Detector"));
	GoalHitbox->SetBoxExtent(FVector(32, 32, 32));
	RootComponent = MySprite;

	GoalHitbox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	GoalHitbox->OnComponentHit.AddDynamic(this, &AGoal::OnCollision);
	
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoal::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit)
{
	UE_LOG(LogTemp, Warning, TEXT("COLLISION"));
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->WinGame();
	}
}

