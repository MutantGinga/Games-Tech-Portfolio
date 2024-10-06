// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutBall.h"
#include "GameLogic.h"
#include "PongBat.h"
#include "BreakoutBrick.h"
#include "BreakoutBat.h"
#include "Engine.h"
#include "Music.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABreakoutBall::ABreakoutBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;
	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball Hit Box"));
	MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MyCollider->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ABreakoutBall::BeginPlay()
{
	Super::BeginPlay();

	BallHalfWidth = MySprite->Bounds.GetBox().GetSize().X / 2;
	MyCollider->SetBoxExtent(FVector(BallHalfWidth, BallHalfWidth, BallHalfWidth));

	MyVelocity = FVector(300, 0, 300);

	SoundPlayer = Cast<AMusic>(UGameplayStatics::GetActorOfClass(GetWorld(), AMusic::StaticClass()));

	AActor* GameCamera = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
	UCameraComponent* GameCameraComponent = Cast<ACameraActor>(GameCamera)->GetCameraComponent();

	HalfPlayFieldHeight = (GameCameraComponent->OrthoWidth / GameCameraComponent->AspectRatio) / 2;
	HalfPlayFieldWidth = (GameCameraComponent->OrthoWidth / 2);

	MyCollider->OnComponentBeginOverlap.AddDynamic(this, &ABreakoutBall::OnOverlapBegin);

}

void ABreakoutBall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->IsA(ABreakoutBat::StaticClass()))
	{ 
		UE_LOG(LogTemp, Warning, TEXT("I HIT SOMETHING!"));
		FVector BatPosition = GetActorLocation();
		MyVelocity.Z = ballSpeed;
		SoundPlayer->PlayBallHitSound();
	}

	else if (OtherActor->IsA(ABreakoutBrick::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("I HIT A BRICK!"));
		ABreakoutBrick* Brick = Cast<ABreakoutBrick>(OtherActor);
		SoundPlayer->PlayBallHitSound();
		if (Brick)
		{
			if (Brick->GetHealth() != 0)
			{
				Brick->ChangeHealth(1);
			}
			if (Brick->GetHealth() == 0)
			{
				OtherActor->Destroy();
			}
		}
		FVector HitDirection = GetActorLocation() - OtherActor->GetActorLocation();
		HitDirection.Normalize();
		if (abs(HitDirection.X) > abs(HitDirection.Z))
		{
			if (HitDirection.X > 0)
			{
				MyVelocity.X = ballSpeed;
			}
			else if (HitDirection.X < 0)
			{
				MyVelocity.X = -ballSpeed;
			}
		}

		else
		{
			if (HitDirection.Z > 0)
			{
				MyVelocity.Z = ballSpeed;
			}
			else if (HitDirection.Z < 0)
			{
				MyVelocity.Z = -ballSpeed;
			}
		}
	}
}

// Called every frame
void ABreakoutBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector MyUpdatedLocation = GetActorLocation() + (MyVelocity * DeltaTime);

	if (MyUpdatedLocation.Z + BallHalfWidth > HalfPlayFieldHeight)
	{
		MyVelocity.Z = -ballSpeed;
	}

	else if (MyUpdatedLocation.Z - BallHalfWidth + 150 < -HalfPlayFieldHeight)
	{
		MyUpdatedLocation = FVector(0, 100, -150);
	}

	if (MyUpdatedLocation.X + BallHalfWidth > (HalfPlayFieldWidth))
	{
		MyVelocity.X = -ballSpeed;
	}

	else if (MyUpdatedLocation.X - BallHalfWidth < (-HalfPlayFieldWidth))
	{
		MyVelocity.X = ballSpeed;
	}

	SetActorLocation(MyUpdatedLocation);

}