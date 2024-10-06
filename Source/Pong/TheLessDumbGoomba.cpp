// Fill out your copyright notice in the Description page of Project Settings.


#include "TheLessDumbGoomba.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

void ATheLessDumbGoomba::BeginPlay()
{
	Super::BeginPlay();

	LeftTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATheLessDumbGoomba::OnLeftOverlap);
	RightTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATheLessDumbGoomba::OnRightOverlap);
}

void ATheLessDumbGoomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MyBodyCollider->AddForce(FVector(WalkingDirection, 0, 0) * EnemyHorizontalAcceleration);

	FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
	ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -EnemyMaxSpeed, EnemyMaxSpeed);
	MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);
}


void ATheLessDumbGoomba::OnLeftOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Left overlap triggered"));

	if (OtherActor->Tags.Contains("Floor"))
	{
		WalkingDirection = 1;
	}

	else if (OtherActor->IsA(AGoomba::StaticClass()))
	{
		WalkingDirection = 1;
	}
}

void ATheLessDumbGoomba::OnRightOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherCmp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Right overlap triggered"));
	if (OtherActor->Tags.Contains("Floor"))
	{
		WalkingDirection = -1;
	}

	else if (OtherActor->IsA(AGoomba::StaticClass()))
	{
		WalkingDirection = -1;
	}
}