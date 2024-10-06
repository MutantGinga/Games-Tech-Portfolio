// Fill out your copyright notice in the Description page of Project Settings.


#include "SawBlade.h"
#include "Mario.h"
#include <PaperFlipbookComponent.h>
#include <Components/BoxComponent.h>

// Sets default values
ASawBlade::ASawBlade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Crate Sprite"));
	KillBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Kill Box"));
	KillBox->SetBoxExtent(FVector(32, 32, 32));

	RootComponent = MySprite;
	KillBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASawBlade::BeginPlay()
{
	Super::BeginPlay();
	Change = NewVector - StartingVector;
	UE_LOG(LogTemp, Warning, TEXT("The distance between EndVector and StartingVector is: %f"), Change);
	StartingVector = GetActorLocation();
	KillBox->OnComponentBeginOverlap.AddDynamic(this, &ASawBlade::OnOverlap);

}

// Called every frame
void ASawBlade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementDirection == 1)
	{
		Change = (NewVector - GetActorLocation()).GetSafeNormal();
	}
	else if (MovementDirection == -1)
	{
		Change = (StartingVector - GetActorLocation()).GetSafeNormal();
	}

	FVector MyUpdatedLocation = GetActorLocation() + (Change * SawSpeed * DeltaTime);

	if (FVector::Dist(MyUpdatedLocation, StartingVector) < 10)
	{
		MovementDirection = 1;
	}
	else if (FVector::Dist(MyUpdatedLocation, NewVector) < 10)
	{
		MovementDirection = -1;
	}

	SetActorLocation(MyUpdatedLocation);
}

void ASawBlade::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision detected with Mario"));
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->KillMario();
	}

}