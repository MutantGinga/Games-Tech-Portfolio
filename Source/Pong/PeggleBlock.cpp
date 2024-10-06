// Fill out your copyright notice in the Description page of Project Settings.


#include "PeggleBlock.h"
#include <Engine.h>
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APeggleBlock::APeggleBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	MySprite->OnComponentHit.AddDynamic(this, &APeggleBlock::OnHit);
	RootComponent = MySprite;

}

// Called when the game starts or when spawned
void APeggleBlock::BeginPlay()
{
	Super::BeginPlay();
	Launcher = Cast<APeggleBallLauncher>(UGameplayStatics::GetActorOfClass(GetWorld(), APeggleBallLauncher::StaticClass()));
	MyQuat = FQuat(FVector(0, 1, 0).GetSafeNormal(), FMath::DegreesToRadians(10));
	MyStartLocation = GetActorLocation();
	MyVelocity = FVector(60, 0, 0);

}

void APeggleBlock::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	MySprite->SetNotifyRigidBodyCollision(true);
}

// Called every frame
void APeggleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (RotateTrue == 1)
	{
		FQuat MyUpdatedRotation = GetActorQuat() * MyQuat;
		SetActorRotation(MyUpdatedRotation);
	}

	if (MoveTrue == 1)
	{
		FVector MyUpdatedLocation = GetActorLocation() + (MyVelocity * DeltaTime);
		SetActorLocation(MyUpdatedLocation);
		if (MyUpdatedLocation.X > MyStartLocation.X + 100 || MyUpdatedLocation.X < MyStartLocation.X -100)
		{
			MyVelocity *= -1;
		}
	}
}

void APeggleBlock::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT!"));
	if (!DestroyTimer.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting Timer"));
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &APeggleBlock::DestroyThisObject, 1.0, false);
	}
}

void APeggleBlock::DestroyThisObject()
{
	if (IsMultiballMaster == 1)
	{
		Launcher->SetMultiballActive(1);
	}

	if (IsSpookyMaster == 1)
	{
		Launcher->SetSpookyActive(1);
	}

	Destroy();
}

