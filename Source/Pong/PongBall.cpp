// Fill out your copyright notice in the Description page of Project Settings.


#include "PongBall.h"
#include "GameLogic.h"
#include "PongBat.h"
#include "Engine.h"
#include "Music.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
APongBall::APongBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;
	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball Hit Box"));
	MyCollider->SetBoxExtent(FVector(32, 32, 32));
	MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MyCollider->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void APongBall::BeginPlay()
{
	Super::BeginPlay();

	MyVelocity = FVector(-ballSpeed, 0, 0);

	GameLogicScoreboard = Cast<AGameLogic>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameLogic::StaticClass()));
	SoundPlayer = Cast<AMusic>(UGameplayStatics::GetActorOfClass(GetWorld(), AMusic::StaticClass()));

	HalfPlayFieldHeight = (2048/1.777) / 2;
	HalfPlayFieldWidth = (2048 / 2);

	MyCollider->OnComponentBeginOverlap.AddDynamic(this, &APongBall::OnOverlapBegin);
	
}

void APongBall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	SoundPlayer->PlayBallHitSound();
	FVector BallPosition = GetActorLocation();
	FVector BatPosition = OtherActor->GetActorLocation();

					//FVector CollisionLocation;
					//FVector BatCenter;

					//if (OtherActor != nullptr && OtherActor->IsA(APongBat::StaticClass()))
					//{
					//	 CollisionLocation = SweepResult.ImpactPoint;
					//	 BatCenter = OtherActor->GetActorLocation();

					//}

	float difference = BatPosition.Z - BallPosition.Z;
	MyVelocity.Z -= difference;// * MyDeltaTime;

	if (difference < -70)
	{
		MyVelocity.Z = ballSpeed * 2;
	}

	else if (-70 <= difference && difference < -50)
	{
		MyVelocity.Z = ballSpeed;
	}

	else if (-50 <= difference && difference < -10)
	{
		MyVelocity.Z = ballSpeed * 0.5;
	}

	else if (-10 <= difference && difference < 10)
	{
		MyVelocity.Z = ballSpeed * 0;
	}

	else if (10 <= difference && difference < 75)
	{
		MyVelocity.Z = ballSpeed  * -0.5;
	}

	else if (75 <= difference && difference < 150)
	{
		MyVelocity.Z = ballSpeed * -1;
	}

	else if (difference >= 150)
	{
		MyVelocity.Z = ballSpeed * -1.5;
	}

	if (BallPosition.X > 0)
	{
		MyVelocity.X = -ballSpeed;
	}

	else if (BallPosition.X < 0)
	{
		MyVelocity.X = ballSpeed;
	}
}

// Called every frame
void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//this->MyDeltaTime = DeltaTime;
	FVector MyUpdatedLocation = GetActorLocation() + (MyVelocity * DeltaTime);
	int PlayerScore = GameLogicScoreboard->GetScore(1);
	int AIScore = GameLogicScoreboard->GetScore(2);

	if (MyUpdatedLocation.Z > HalfPlayFieldHeight)
	{
		MyVelocity.Z = -ballSpeed;
	}

	else if (MyUpdatedLocation.Z < -HalfPlayFieldHeight)
	{
		MyVelocity.Z = ballSpeed;
	}

	if (MyUpdatedLocation.X > (HalfPlayFieldWidth + 500))
	{
		MyUpdatedLocation = FVector(500, 900, 0);
		GameLogicScoreboard->IncrementScore(1, 1);
		if (PlayerScore == 10)
		{
			GameLogicScoreboard->YouWon();
		}
	}

	else if (MyUpdatedLocation.X < (-HalfPlayFieldHeight + 30))
	{
		MyUpdatedLocation = FVector(500, 900, 0);
		GameLogicScoreboard->IncrementScore(2, 1);
		if (AIScore == 10)
		{
			GameLogicScoreboard->YouLost();
		}
	}

	SetActorLocation(MyUpdatedLocation);

}

